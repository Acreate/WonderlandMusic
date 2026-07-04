#include "musicContreWidget.h"

#include <QDateTime>
#include <QPainter>
#include <qevent.h>

#include "playerListTopWidget.h"

#include "../application/appDrawManage.h"
#include "../application/appInstance.h"
#include "../application/appRenderImage.h"
#include "../application/appUserInterfaceManage.h"

#include "../item/musicItem.h"

#include "../itemWidget/musicInfoItemWidget.h"

#include "../mutex/userMutex.h"

#include "../tools/vectorTools.h"

MusicContreWidget::MusicContreWidget( QWidget *parent ) : QWidget( parent ) {
}

bool MusicContreWidget::showFavorteMusicContreList( const QString &music_favorte_widget ) {
	return false;
}

void MusicContreWidget::setItemVector( const std::vector< MusicItem * > &load_music_items ) {
	size_t count = load_music_items.size( );
	auto data = load_music_items.data( );
	size_t index;
	musicInfoMutex->lock( );
	size_t oldSize = musicInfoVector.size( );
	size_t newsize = count + oldSize;
	musicInfoVector.resize( newsize );
	auto saveInfoData = musicInfoVector.data( );
	auto offsetPtr = saveInfoData + oldSize;
	size_t findIndex;

	for( index = 0; index < count; index += 1 ) {
		auto musicItem = data[ index ];
		auto absfile = musicItem->getAbsFilePath( );
		for( findIndex = 0; findIndex < oldSize; findIndex += 1 )
			if( saveInfoData[ findIndex ]->isFile( absfile ) )
				break;
		if( findIndex < oldSize )
			continue;
		auto musicInfoItemWidget = new MusicInfoItemWidget( *musicItem );
		offsetPtr[ index ] = musicInfoItemWidget;
		oldSize += 1;
	}
	if( oldSize != newsize )
		musicInfoVector.resize( oldSize );
	musicInfoMutex->unlock( );
	updateItemWidget( );
}

void MusicContreWidget::setItemPlayerListTopWidgetWidth( const PlayerListTopWidget *player_list_top_widget ) {
	int widgetBeforeWidth = player_list_top_widget->getWidgetBeforeWidth( );
	int splitWidth = player_list_top_widget->getSplitWidth( );
	int musicNameWidth = player_list_top_widget->getMusicNameWidth( );
	int musicSingerWidth = player_list_top_widget->getMusicSingerWidth( );
	int musicDurationWidth = player_list_top_widget->getMusicDurationWidth( );
	int widgetAfterWidth = player_list_top_widget->getWidgetAfterWidth( );
	int indexWidth = player_list_top_widget->getIndexWidth( );
	setItemWidth( widgetBeforeWidth, splitWidth, indexWidth, musicNameWidth, musicSingerWidth, musicDurationWidth, widgetAfterWidth );
}

void MusicContreWidget::setItemWidth( int widget_before_width, int splite_width, int index_width, int music_name_width, int music_singer_width, int music_duration_width, int widget_after_width ) {
	widgetBeforeWidth = widget_before_width;
	splitWidth = splite_width;
	musicNameWidth = music_name_width;
	musicSingerWidth = music_singer_width;
	musicDurationWidth = music_duration_width;
	widgetAfterWidth = widget_after_width;
	indexWidth = index_width;
	updateItemWidget( );
}

void MusicContreWidget::updateItemWidget( ) {
	if( musicInfoMutex == nullptr )
		return;
	musicInfoMutex->lock( );

	int offsetY = 0;
	auto appInstance = AppInstance::getAppInstance( );
	auto appDrawManage = appInstance->getAppUserInterfaceManage( )->getAppDrawManage( );
	auto renderImage = appDrawManage->getAppRenderImage( );
	auto fontMetrics = renderImage->getFontMetrics( );
	int height = fontMetrics->height( );
	auto newWidth = this->widgetBeforeWidth + this->widgetAfterWidth + this->splitWidth * 5 + this->musicNameWidth + this->musicSingerWidth + this->musicDurationWidth + this->indexWidth;
	size_t count = musicInfoVector.size( );
	if( count == 0 ) {
		if( newWidth > 0 )
			setFixedWidth( newWidth );
		musicInfoMutex->unlock( );
		return;
	}
	decltype(musicInfoVector) buff;
	// 删除空指针
	VectorTools::removeNullptrVectorPtr( buff, musicInfoVector );
	musicInfoVector = buff;
	// 删除重复
	removeRepetition( );
	count = musicInfoVector.size( );

	auto data = musicInfoVector.data( );
	size_t index;
	for( index = 0; index < count; index += 1 ) {
		auto itemWidget = data[ index ];
		itemWidget->setItemWidth( widgetBeforeWidth, widgetAfterWidth, splitWidth, indexWidth, musicNameWidth, musicSingerWidth, musicDurationWidth );
		itemWidget->setIndex( index + 1 );
		itemWidget->update( );
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

void MusicContreWidget::removeRepetition( ) {
	using compUnity = MusicInfoItemWidget *;
	VectorTools::compIdenticalTypeFinction< compUnity > compFunction = [] ( const compUnity &left, const compUnity &right ) ->bool {
		if( left->isFile( right ) )
			return true;
		return false;
	};
	std::vector< MusicInfoItemWidget * > release;
	std::vector< MusicInfoItemWidget * > buff;
	VectorTools::getRepetition( buff, release, musicInfoVector, compFunction );
	VectorTools::deleteVectorPtr( release );
	musicInfoVector = buff;
}

void MusicContreWidget::apendSelectMusicItemWidget( MusicInfoItemWidget *append_select_target, bool check_key_board_modifier ) {
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
				selectItemWidgetVector.resize( 1 );
				auto musicInfoItemWidget = selectItemWidgetVector.data( );
				musicInfoItemWidget[ 0 ] = selectLeftItemWidget;
			}
		}
	}
}

bool MusicContreWidget::selectKeyShiftModifier( ) {
	auto count = selectItemWidgetVector.size( );
	if( count > 0 ) {
		auto selectItemWidgetData = selectItemWidgetVector.data( );
		auto findFirstItemWidth = selectItemWidgetData[ 0 ];
		size_t musicCount = musicInfoVector.size( );
		auto findSourceData = musicInfoVector.data( );
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
				selectItemWidgetVector.resize( count );
				selectItemWidgetData = selectItemWidgetVector.data( );
				findSourceData += getBegIndex;
				musicIndex = 0;
				for( ; musicIndex < count; musicIndex += 1 )
					selectItemWidgetData[ musicIndex ] = findSourceData[ musicIndex ];
			} else {
				auto endIndex = getBegIndex + 1;
				count = endIndex - getEndIndex;
				selectItemWidgetVector.resize( count );
				selectItemWidgetData = selectItemWidgetVector.data( );
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

bool MusicContreWidget::selectKeyControlModifier( ) {
	auto count = selectItemWidgetVector.size( );
	if( count ) {
		auto musicInfoItemWidget = selectItemWidgetVector.data( );
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
	selectItemWidgetVector.emplace_back( selectLeftItemWidget );
	return true;
}

bool MusicContreWidget::deleteResource( ) {
	disconnect( );
	return true;
}

bool MusicContreWidget::init( ) {
	return true;
}

bool MusicContreWidget::initBefore( ) {
	deleteResource( );
	doubleClickIntervalTimeMilliSecond = 300;
	activeLeftItemWidget = nullptr;
	selectLeftItemWidget = nullptr;
	musicInfoMutex = new UserMutex;
	beforeClickTime = new QDateTime;
	pen = new QPen;
	drawPenWidth = 4;
	drawPenColor = QColor( "#7bffa1" );
	drawFillColor = QColor( "#50a2ff" );
	drawFillColor.setAlpha( 100 );
	pen->setWidth( drawPenWidth );
	pen->setColor( drawPenColor );
	indexWidth = splitWidth = musicNameWidth = musicSingerWidth = musicDurationWidth = 4;
	return true;
}

bool MusicContreWidget::initAfter( ) {
	auto interfaceManage = AppInstance::getAppInstance( )->getAppUserInterfaceManage( );
	connect( interfaceManage, &AppUserInterfaceManage::signal_changed_width, this, &MusicContreWidget::setItemWidth );
	updateItemWidget( );
	return true;
}

void MusicContreWidget::paintEvent( QPaintEvent *event ) {
	if( musicInfoMutex == nullptr || musicInfoMutex->tryLock( ) == false )
		return;
	QPainter painter;
	painter.begin( this );
	painter.setPen( *pen );
	size_t count = selectItemWidgetVector.size( );
	if( count ) {
		auto data = selectItemWidgetVector.data( );
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

void MusicContreWidget::resizeEvent( QResizeEvent *event ) {
	auto size = event->size( );
	currentWidgetHeight = size.height( );
	currentWidgetWidth = size.width( );
}

void MusicContreWidget::mouseMoveEvent( QMouseEvent *event ) {
	if( musicInfoMutex->tryLock( ) == false )
		return;
	size_t count = musicInfoVector.size( );
	if( count == 0 ) {
		musicInfoMutex->unlock( );
		return;
	}

	auto point = event->pos( );
	auto data = musicInfoVector.data( );
	size_t index;
	for( index = 0; index < count; index += 1 )
		if( data[ index ]->geometry( ).contains( point ) ) {
			activeLeftItemWidget = data[ index ];
			break;
		}
	musicInfoMutex->unlock( );
	update( );
}

void MusicContreWidget::mouseReleaseEvent( QMouseEvent *event ) {
	Qt::MouseButton mouseButton = event->button( );
	switch( mouseButton ) {
		case Qt::MouseButton::LeftButton : {
			bool isDoubleClick = false;
			MusicInfoItemWidget *selectItem = nullptr;
			musicInfoMutex->lock( );
			size_t count = musicInfoVector.size( );
			if( count == 0 ) {
				musicInfoMutex->unlock( );
				return;
			}

			auto point = event->pos( );
			auto data = musicInfoVector.data( );
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
				emit signal_item_double_select( );
			} else if( selectItem ) { // 单击
				std::vector< MusicInfoItemWidget * > resultVector;
				musicInfoMutex->lock( );
				apendSelectMusicItemWidget( selectItem, true );
				resultVector = selectItemWidgetVector;
				musicInfoMutex->unlock( );
				// 触发信号
				emit signal_item_select( );
				update( );
			}
		}
		break;
		case Qt::MouseButton::RightButton : {
			MusicInfoItemWidget *selectItem = nullptr;
			musicInfoMutex->lock( );

			size_t count = musicInfoVector.size( );
			if( count ) {
				auto point = event->pos( );
				auto data = musicInfoVector.data( );
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
				resultVector = selectItemWidgetVector;
				musicInfoMutex->unlock( );
				update( );
				// 触发信号
				emit signal_item_select( );
			}
		}
		break;
	}
}
