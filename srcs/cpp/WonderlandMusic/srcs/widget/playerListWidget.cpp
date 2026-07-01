#include "playerListWidget.h"

#include <QPaintEvent>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QUrl>
#include <QPainter>
#include <mutex>

#include "playerListTopWidget.h"

#include "../application/appDataManage.h"
#include "../application/appDrawManage.h"
#include "../application/appInstance.h"
#include "../application/appTranslate.h"
#include "../application/musicDecoder.h"
#include "../application/renderImage.h"
#include "../application/translate/playerListWidgetTranslate.h"

#include "../item/musicInfoItem.h"

#include "../itemWidget/musicInfoItemWidget.h"

#include "../msgInfo/messageErrorOut.h"

#include "../mutex/userMutex.h"

#include "../tools/arrayTools.h"
#include "../tools/pathTools.h"
#include "../tools/vectorTools.h"

#include "../window/playerWindow.h"

void PlayerListWidget::clearMusicInfoVector( ) {
	musicInfoMutex->lock( );
	musicInfoVector->clear( );
	musicInfoMutex->unlock( );
}

PlayerListWidget::~PlayerListWidget( ) {
	deleteResource( );
}

PlayerListWidget::PlayerListWidget( PlayerWindow *parent ) : QWidget( parent ), parentContent( parent ) {
	setMouseTracking( true );
}

void PlayerListWidget::setItemWidth( const PlayerListTopWidget *player_list_top_widget ) {
	int widgetBeforeWidth = player_list_top_widget->getWidgetBeforeWidth( );
	int splitWidth = player_list_top_widget->getSplitWidth( );
	int musicNameWidth = player_list_top_widget->getMusicNameWidth( );
	int musicSingerWidth = player_list_top_widget->getMusicSingerWidth( );
	int musicDurationWidth = player_list_top_widget->getMusicDurationWidth( );
	int widgetAfterWidth = player_list_top_widget->getWidgetAfterWidth( );
	int indexWidth = player_list_top_widget->getIndexWidth( );
	setItemWidth( widgetBeforeWidth, splitWidth, indexWidth, musicNameWidth, musicSingerWidth, musicDurationWidth, widgetAfterWidth );
}

void PlayerListWidget::setItemWidth( int widget_before_width, int splite_width, int index_width, int music_name_width, int music_singer_width, int music_duration_width, int widget_after_width ) {
	widgetBeforeWidth = widget_before_width;
	splitWidth = splite_width;
	musicNameWidth = music_name_width;
	musicSingerWidth = music_singer_width;
	musicDurationWidth = music_duration_width;
	widgetAfterWidth = widget_after_width;
	indexWidth = index_width;
	updateItemWidget( );
}

int PlayerListWidget::getSplitWidth( ) const {
	return splitWidth;
}

int PlayerListWidget::getMusicNameWidth( ) const {
	return musicNameWidth;
}

int PlayerListWidget::getMusicSingerWidth( ) const {
	return musicSingerWidth;
}

int PlayerListWidget::getMusicDurationWidth( ) const {
	return musicDurationWidth;
}

MusicInfoItemWidget * PlayerListWidget::getActiveLeftItemWidget( ) const {
	return activeLeftItemWidget;
}

MusicInfoItemWidget * PlayerListWidget::getSelectLeftItemWidget( ) const {
	return selectLeftItemWidget;
}

std::vector< MusicInfoItemWidget * > & PlayerListWidget::getSelectItemWidgetVector( std::vector< MusicInfoItemWidget * > &result_vector ) const {
	musicInfoMutex->lock( );
	result_vector = *selectItemWidgetVector;
	musicInfoMutex->unlock( );
	return result_vector;
}

void PlayerListWidget::setWidgetMusicInfoVector( std::vector< MusicInfoItemWidget * > &new_vector ) const {
	musicInfoMutex->lock( );
	*musicInfoVector = new_vector;
	musicInfoMutex->unlock( );
}

std::vector< MusicInfoItemWidget * > & PlayerListWidget::getWidgetMusicInfoVector( std::vector< MusicInfoItemWidget * > &result_vector ) const {
	musicInfoMutex->lock( );
	result_vector = *musicInfoVector;
	musicInfoMutex->unlock( );
	return result_vector;
}

std::vector< QString > & PlayerListWidget::getListMusicFile( std::vector< QString > &result_vector ) const {
	musicInfoMutex->lock( );

	size_t count = musicInfoVector->size( );
	if( count == 0 ) {
		musicInfoMutex->unlock( );
		return result_vector;
	}

	result_vector.resize( count );
	auto copyToData = result_vector.data( );
	auto musicInfoData = musicInfoVector->data( );
	size_t index;
	for( index = 0; index < count; index += 1 )
		copyToData[ index ] = musicInfoData[ index ]->getMusicFilePath( );

	index = count;
	count = loadMusicFileHistory.size( );
	auto loadMusciFileHistoryData = loadMusicFileHistory.data( );
	size_t newSize = count + index;
	result_vector.resize( newSize );
	copyToData = result_vector.data( ) + index;
	for( index = 0; index < count; index += 1 )
		copyToData[ index ] = loadMusciFileHistoryData[ index ];
	musicInfoMutex->unlock( );
	return result_vector;
}

qint64 PlayerListWidget::getMusicDuratction( ) const {
	return 0;
}

bool PlayerListWidget::init( ) {
	deleteResource( );

	musicInfoMutex = new UserMutex;
	doubleClickIntervalTimeMilliSecond = 300;
	activeLeftItemWidget = nullptr;
	selectLeftItemWidget = nullptr;
	beforeClickTime = new QDateTime;
	pen = new QPen;
	selectItemWidgetVector = new std::vector< MusicInfoItemWidget * >;
	musicInfoVector = new std::vector< MusicInfoItemWidget * >;
	indexWidth = splitWidth = musicNameWidth = musicSingerWidth = musicDurationWidth = 4;
	drawPenWidth = 4;
	drawPenColor = QColor( "#7bffa1" );
	drawFillColor = QColor( "#50a2ff" );
	drawFillColor.setAlpha( 100 );
	pen->setWidth( drawPenWidth );
	pen->setColor( drawPenColor );

	updateItemWidget( );

	return true;
}

void PlayerListWidget::clear( ) {
	musicInfoMutex->lock( );
	musicInfoVector->clear( );
	musicInfoMutex->unlock( );
}

void PlayerListWidget::apendSelectMusicItemWidget( MusicInfoItemWidget *append_select_target, bool check_key_board_modifier ) {
	activeLeftItemWidget = append_select_target;
	selectLeftItemWidget = append_select_target;
	if( check_key_board_modifier == false )
		selectKeyControlModifier( );
	else {
		auto appInstance = AppInstance::getAppInstance( );
		auto keyboardModifiers = ( Qt::KeyboardModifier ) appInstance->keyboardModifiers( ).toInt( );
		switch( keyboardModifiers ) {
			case Qt::KeyboardModifier::ControlModifier :
				selectKeyControlModifier( );
				break;
			case Qt::KeyboardModifier::ShiftModifier :
				if( selectKeyShiftModifier( ) == true )
					break;
			default : {
				selectItemWidgetVector->resize( 1 );
				auto musicInfoItemWidget = selectItemWidgetVector->data( );
				musicInfoItemWidget[ 0 ] = selectLeftItemWidget;
			}
		}
	}
}

bool PlayerListWidget::selectKeyShiftModifier( ) {
	auto count = selectItemWidgetVector->size( );
	if( count > 0 ) {
		auto selectItemWidgetData = selectItemWidgetVector->data( );
		auto findFirstItemWidth = selectItemWidgetData[ 0 ];
		size_t musicCount = musicInfoVector->size( );
		auto findSourceData = musicInfoVector->data( );
		size_t musicIndex = 0;
		// 匹配 getBegIndex
		for( ; musicIndex < musicCount; musicIndex += 1 )
			if( findSourceData[ musicIndex ] == findFirstItemWidth )
				break;
		if( musicIndex == musicCount )
			return false;

		size_t getBegIndex = musicIndex;

		// 匹配 getEndIndex
		for( musicIndex = 0; musicIndex < musicCount; musicIndex += 1 )
			if( findSourceData[ musicIndex ] == selectLeftItemWidget )
				break;
		if( musicIndex == musicCount )
			return false;

		size_t getEndIndex = musicIndex;
		if( getEndIndex != getBegIndex ) {
			if( getEndIndex > getBegIndex ) {
				auto endIndex = getEndIndex + 1;
				count = endIndex - getBegIndex;
				selectItemWidgetVector->resize( count );
				selectItemWidgetData = selectItemWidgetVector->data( );
				findSourceData += getBegIndex;
				musicIndex = 0;
				for( ; musicIndex < count; musicIndex += 1 )
					selectItemWidgetData[ musicIndex ] = findSourceData[ musicIndex ];
			} else {
				auto endIndex = getBegIndex + 1;
				count = endIndex - getEndIndex;
				selectItemWidgetVector->resize( count );
				selectItemWidgetData = selectItemWidgetVector->data( );
				findSourceData += getEndIndex;
				qint64 destIndex = count - 1;
				musicIndex = 0;
				for( ; musicIndex < count; musicIndex += 1, destIndex -= 1 )
					selectItemWidgetData[ destIndex ] = findSourceData[ musicIndex ];
			}
		}
		return true;
	}
	return false; // 未处理
}

bool PlayerListWidget::selectKeyControlModifier( ) {
	auto count = selectItemWidgetVector->size( );
	if( count ) {
		auto musicInfoItemWidget = selectItemWidgetVector->data( );
		size_t index = 0;
		for( ; index < count; index += 1 )
			if( musicInfoItemWidget[ index ] == selectLeftItemWidget )
				break;
		if( index < count ) {
			count -= 1;
			for( ; index < count; index += 1 )
				musicInfoItemWidget[ index ] = musicInfoItemWidget[ index + 1 ];
			musicInfoItemWidget[ index ] = selectLeftItemWidget; // 排序到末尾
			return true;
		}
	}
	selectItemWidgetVector->emplace_back( selectLeftItemWidget );
	return true;
}

bool PlayerListWidget::deleteResource( ) {
	disconnect( );
	if( musicInfoMutex ) {
		musicInfoMutex->lock( );
		if( selectItemWidgetVector )
			Delete_Resource_App_Core_Ptr( selectItemWidgetVector );
		Delete_Resource_App_Core_Ptr( selectItemWidgetVector );

		selectLeftItemWidget = nullptr;
		activeLeftItemWidget = nullptr;

		musicInfoMutex->unlock( );
		clearMusicInfoVector( );
		if( musicInfoVector ) {
			Delete_Resource_App_Core_Ptr( musicInfoVector );
		}
		Delete_Resource_App_Core_Ptr( musicInfoMutex );

		Delete_Resource_App_Core_Ptr( beforeClickTime );
		Delete_Resource_App_Core_Ptr( pen );
	}
	return true;
}

void PlayerListWidget::removeRepetition( ) {
	using compUnity = MusicInfoItemWidget *;
	VectorTools::compIdenticalTypeFinction< compUnity > compFunction = [] ( const compUnity &left, const compUnity &right ) ->bool {
		if( left->musicFilePath == right->musicFilePath )
			return true;
		return false;
	};
	std::vector< MusicInfoItemWidget * > release;
	std::vector< MusicInfoItemWidget * > buff;
	VectorTools::getRepetition( buff, release, *musicInfoVector, compFunction );
	VectorTools::deleteVectorPtr( release );
	*musicInfoVector = buff;
}

void PlayerListWidget::updateItemWidget( ) {
	musicInfoMutex->lock( );

	int offsetY = 0;
	auto appInstance = AppInstance::getAppInstance( );
	auto renderImage = appInstance->getAppDrawManage( )->getRenderImage( );
	auto fontMetrics = renderImage->getFontMetrics( );
	int height = fontMetrics->height( );
	auto newWidth = this->widgetBeforeWidth + this->widgetAfterWidth + this->splitWidth * 5 + this->musicNameWidth + this->musicSingerWidth + this->musicDurationWidth + this->indexWidth;
	size_t count = musicInfoVector->size( );
	if( count == 0 ) {
		if( newWidth > 0 )
			setFixedWidth( newWidth );
		musicInfoMutex->unlock( );
		return;
	}
	decltype(musicInfoVector) buff = new std::vector< MusicInfoItemWidget * >;
	// 删除空指针
	VectorTools::removeNullptrVectorPtr( *buff, *musicInfoVector );
	*musicInfoVector = *buff;
	// 删除重复
	removeRepetition( );
	count = musicInfoVector->size( );
	delete buff;
	auto data = musicInfoVector->data( );
	size_t index;
	for( index = 0; index < count; index += 1 ) {
		auto itemWidget = data[ index ];
		itemWidget->widgetBeforeWidth = this->widgetBeforeWidth;
		itemWidget->widgetAfterWidth = this->widgetAfterWidth;
		itemWidget->splitWidth = this->splitWidth;
		itemWidget->musicNameWidth = this->musicNameWidth;
		itemWidget->musicSingerWidth = this->musicSingerWidth;
		itemWidget->musicDurationWidth = this->musicDurationWidth;
		itemWidget->indexWidth = this->indexWidth;
		itemWidget->setIndex( index + 1 );
		itemWidget->update( );
		itemWidget->show( );
		itemWidget->setGeometry( 0, offsetY, newWidth, height );
		offsetY += height;
	}
	if( offsetY > 0 && newWidth > 0 )
		this->setFixedSize( newWidth, offsetY );
	else if( offsetY == 0 && newWidth > 0 )
		setFixedWidth( newWidth );
	else if( offsetY > 0 && newWidth == 0 )
		setFixedHeight( offsetY );
	musicInfoMutex->unlock( );
}

void PlayerListWidget::paintEvent( QPaintEvent *event ) {
	if( musicInfoMutex->tryLock( ) == false )
		return;
	QPainter painter;
	painter.begin( this );
	painter.setPen( *pen );
	size_t count = selectItemWidgetVector->size( );
	if( count ) {
		auto data = selectItemWidgetVector->data( );
		size_t index;
		for( index = 0; index < count; index += 1 )
			painter.fillRect( data[ index ]->geometry( ), drawFillColor );
	}
	if( activeLeftItemWidget ) {
		auto drawPenWidthOffset = drawPenWidth / 2;
		auto geometry = activeLeftItemWidget->geometry( );
		int x = geometry.x( ) + drawPenWidthOffset;
		int y = geometry.y( ) + drawPenWidthOffset;
		int width = geometry.width( ) - drawPenWidth;
		int height = geometry.height( ) - drawPenWidth;

		painter.drawRect( x, y, width, height );
	}
	painter.end( );
	musicInfoMutex->unlock( );
}

void PlayerListWidget::resizeEvent( QResizeEvent *event ) {
	auto size = event->size( );
	currentWidgetHeight = size.height( );
	currentWidgetWidth = size.width( );
	//update();
}

void PlayerListWidget::mouseMoveEvent( QMouseEvent *event ) {
	if( musicInfoMutex->tryLock( ) == false )
		return;
	size_t count = musicInfoVector->size( );
	if( count == 0 ) {
		musicInfoMutex->unlock( );
		return;
	}

	auto point = event->pos( );
	auto data = musicInfoVector->data( );
	size_t index;
	for( index = 0; index < count; index += 1 )
		if( data[ index ]->geometry( ).contains( point ) ) {
			activeLeftItemWidget = data[ index ];
			break;
		}
	musicInfoMutex->unlock( );
	update( );
}

void PlayerListWidget::mouseReleaseEvent( QMouseEvent *event ) {
	Qt::MouseButton mouseButton = event->button( );
	switch( mouseButton ) {
		case Qt::MouseButton::LeftButton : {
			bool isDoubleClick = false;
			MusicInfoItemWidget *selectItem = nullptr;
			musicInfoMutex->lock( );
			size_t count = musicInfoVector->size( );
			if( count == 0 ) {
				musicInfoMutex->unlock( );
				return;
			}

			auto point = event->pos( );
			auto data = musicInfoVector->data( );
			size_t index;
			for( index = 0; index < count; index += 1 )
				if( data[ index ]->geometry( ).contains( point ) ) {
					selectItem = data[ index ];

					// 双击检测
					auto currentDateTime = QDateTime::currentDateTime( );
					if( selectLeftItemWidget == selectItem )
						isDoubleClick = doubleClickIntervalTimeMilliSecond > ( currentDateTime - *beforeClickTime ).count( );
					*beforeClickTime = currentDateTime;
					break;
				}
			musicInfoMutex->unlock( );
			// 双击或单击，二选一
			if( isDoubleClick ) {
				// 触发信号
				emit itemDouble_Select( );
			} else if( selectItem ) { // 单击
				std::vector< MusicInfoItemWidget * > resultVector;
				musicInfoMutex->lock( );
				apendSelectMusicItemWidget( selectItem, true );
				resultVector = *selectItemWidgetVector;
				musicInfoMutex->unlock( );
				// 触发信号
				emit itemSelect( );
				update( );
			}
		}
		break;
		case Qt::MouseButton::RightButton : {
			MusicInfoItemWidget *selectItem = nullptr;
			musicInfoMutex->lock( );

			size_t count = musicInfoVector->size( );
			if( count ) {
				auto point = event->pos( );
				auto data = musicInfoVector->data( );
				size_t index;
				for( index = 0; index < count; index += 1 )
					if( data[ index ]->geometry( ).contains( point ) ) {
						selectItem = data[ index ];
						break;
					}
			}
			musicInfoMutex->unlock( );
			if( selectItem ) {
				std::vector< MusicInfoItemWidget * > resultVector;
				musicInfoMutex->lock( );
				apendSelectMusicItemWidget( selectItem, false );
				resultVector = *selectItemWidgetVector;
				musicInfoMutex->unlock( );
				update( );
				// 触发信号
				emit itemSelect( );
			}
			// 触发信号
			emit popMenu( );
		}
		break;
	}
}
