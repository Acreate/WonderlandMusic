#include "playerListWidget.h"

#include <QPaintEvent>
#include <QJsonObject>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QUrl>
#include <QMutex>
#include <QPainter>

#include "playerListTopWidget.h"

#include "../application/appInstance.h"
#include "../application/appTranslate.h"
#include "../application/jsonFileKey.h"
#include "../application/renderImage.h"

#include "../item/musicInfoItem.h"

#include "../itemWidget/musicInfoItemWidget.h"

#include "../menu/playerWidgetMenu.h"

#include "../msgInfo/messageErrorOut.h"

#include "../thread/widgetThread.h"

#include "../tools/pathTools.h"

void PlayerListWidget::clearMusicInfoVector( ) {
	loadMusicFileMutex->lock( );
	auto count = musicInfoVector.size( );
	if( count ) {
		auto data = musicInfoVector.data( );
		decltype(count) index = 0;
		for( ; index < count; index += 1 )
			delete data[ index ];
		musicInfoVector.clear( );
	}
	loadMusicFileMutex->unlock( );
}

PlayerListWidget::~PlayerListWidget( ) {
	clearMusicInfoVector( );
	selectItemMutex->lock( );
	selectItemWidgetVector.clear( );
	selectLeftItemWidget = nullptr;
	activeLeftItemWidget = nullptr;
	selectItemMutex->unlock( );
	delete playerWidgetMenu;
	delete loadMusicFileMutex;
	delete beforeClickTime;
	delete pen;
	delete selectItemMutex;
}

PlayerListWidget::PlayerListWidget( QWidget *parent ) : QWidget( parent ) {
	doubleClickIntervalTimeMilliSecond = 300;
	activeLeftItemWidget = nullptr;
	selectLeftItemWidget = nullptr;
	loadMusicFileMutex = new QMutex;
	selectItemMutex = new QMutex;
	beforeClickTime = new QDateTime;
	playerWidgetMenu = new PlayerWidgetMenu( this );
	pen = new QPen;
	indexWidth = splitWidth = musicNameWidth = musicSingerWidth = musicDurationWidth = 4;
	drawPenWidth = 4;
	drawPenColor = QColor( "#7bffa1" );
	drawFillColor = QColor( "#50a2ff" );
	drawFillColor.setAlpha( 100 );
	pen->setWidth( drawPenWidth );
	pen->setColor( drawPenColor );

	updateItemWidget( );
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

void PlayerListWidget::setSplitWidth( const int split_width ) {
	splitWidth = split_width;
	updateItemWidget( );
}

int PlayerListWidget::getMusicNameWidth( ) const {
	return musicNameWidth;
}

void PlayerListWidget::setMusicNameWidth( const int music_name_width ) {
	musicNameWidth = music_name_width;
	updateItemWidget( );
}

int PlayerListWidget::getMusicSingerWidth( ) const {
	return musicSingerWidth;
}

void PlayerListWidget::setMusicSingerWidth( const int music_singer_width ) {
	musicSingerWidth = music_singer_width;
	updateItemWidget( );
}

int PlayerListWidget::getMusicDurationWidth( ) const {
	return musicDurationWidth;
}

void PlayerListWidget::setMusicDurationWidth( const int format_string_duration_width ) {
	musicDurationWidth = format_string_duration_width;
	updateItemWidget( );
}

MusicInfoItemWidget * PlayerListWidget::getActiveLeftItemWidget( ) const {
	return activeLeftItemWidget;
}

MusicInfoItemWidget * PlayerListWidget::getSelectLeftItemWidget( ) const {
	return selectLeftItemWidget;
}

QVector< MusicInfoItemWidget * > & PlayerListWidget::getSelectItemWidgetVector( QVector< MusicInfoItemWidget * > &result_vector ) const {
	selectItemMutex->lock( );
	result_vector = selectItemWidgetVector;
	selectItemMutex->unlock( );
	return result_vector;
}

bool PlayerListWidget::loadJsonPathInfo( ) {
	if( playerWidgetMenu->init( ) == false )
		return false;
	auto appInstance = AppInstance::getAppInstance( );
	auto jsonFileKey = appInstance->getJsonFileKey( );
	auto fileJsonPath = jsonFileKey->getMusicPlayerListInfoFileJsonPath( );
	QJsonObject fileJsonObject;
	if( PathTools::readJsonObject( fileJsonObject, fileJsonPath ) == false )
		return true;
	auto end = fileJsonObject.end( );
	QJsonObject::iterator find;

	find = fileJsonObject.find( jsonFileKey->getMusicInfoListCount( ) );
	if( end == find )
		return true;
	qint64 count = find.value( ).toInteger( );
	if( count == 0 )
		return true;
	find = fileJsonObject.find( jsonFileKey->getMusicInfoListName( ) );
	if( end == find )
		return true;

	QJsonObject subJsonObject;
	subJsonObject = find.value( ).toObject( );
	auto foreachIterator = subJsonObject.begin( );
	auto foreachEnd = subJsonObject.end( );

	decltype(musicInfoVector) buff( count, nullptr );
	auto maxIndex = count - 1;
	auto data = buff.data( );
	for( ; foreachIterator != foreachEnd; ++foreachIterator ) {
		auto indexJsonKey = foreachIterator.key( );
		bool isConverOk;
		auto converResultIndex = indexJsonKey.toULongLong( &isConverOk );
		if( isConverOk == false )
			continue;
		if( converResultIndex > maxIndex )
			continue;
		auto musicInfoJsonObject = foreachIterator.value( ).toObject( );
		auto ctreaItem = new MusicInfoItemWidget( this );
		if( MusicInfoItem::forJsonObject( *ctreaItem, musicInfoJsonObject ) == false ) {
			delete ctreaItem;
			continue;
		}
		ctreaItem->parentPlayListWidget = this;
		data[ converResultIndex ] = ctreaItem;
	}

	loadMusicFileMutex->lock( );
	auto oldCount = musicInfoVector.size( );
	decltype(musicInfoVector) releaseVector( oldCount, nullptr );
	auto buffToData = releaseVector.data( );
	auto copyToData = musicInfoVector.data( );
	for( maxIndex = 0; maxIndex < oldCount; maxIndex += 1 )
		buffToData[ maxIndex ] = copyToData[ maxIndex ];
	musicInfoVector.resize( count );
	copyToData = musicInfoVector.data( );
	for( maxIndex = 0; maxIndex < count; maxIndex += 1 )
		copyToData[ maxIndex ] = data[ maxIndex ];
	loadMusicFileMutex->unlock( );

	for( maxIndex = 0; maxIndex < oldCount; maxIndex += 1 )
		delete buffToData[ maxIndex ];
	updateItemWidget( );
	return true;
}

bool PlayerListWidget::writeJsonPathInfo( ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto jsonFileKey = appInstance->getJsonFileKey( );

	QJsonObject fileJsonObject;

	loadMusicFileMutex->lock( );
	qsizetype count = musicInfoVector.size( );
	if( count == 0 ) {
		loadMusicFileMutex->unlock( );
		return true;
	}
	auto sourceData = musicInfoVector.data( );
	decltype(musicInfoVector) buff( count );
	auto destData = buff.data( );
	qsizetype index = 0;
	for( ; index < count; index += 1 )
		destData[ index ] = sourceData[ index ];
	loadMusicFileMutex->unlock( );
	fileJsonObject.insert( jsonFileKey->getMusicInfoListCount( ), count );

	QJsonObject arrayJsonObject;

	for( index = 0; index < count; index += 1 ) {
		QJsonObject subJsonObject;
		if( MusicInfoItem::toJsonObect( subJsonObject, *destData[ index ] ) == false )
			continue;
		arrayJsonObject.insert( QString::number( index ), subJsonObject );
	}

	fileJsonObject.insert( jsonFileKey->getMusicInfoListName( ), arrayJsonObject );

	auto fileJsonPath = jsonFileKey->getMusicPlayerListInfoFileJsonPath( );
	PathTools::writeJsonObject( fileJsonObject, fileJsonPath );
	return true;
}

bool PlayerListWidget::appendItem( const QString &music_file_path, const QString &music_name, const QString &music_singer, const qint64 &duration ) {
	QFileInfo fileInfo( music_file_path );
	bool resultBool = true;
	auto absFilePath = fileInfo.absoluteFilePath( );
	loadMusicFileMutex->lock( );

	qsizetype count = loadMusicFileHistory.size( );
	if( count ) {
		qsizetype index = 0;
		auto data = loadMusicFileHistory.data( );
		for( ; index < count; index += 1 )
			if( data[ index ] == absFilePath ) {
				loadMusicFileMutex->unlock( );
				return false; // 已经在任务列表
			}
	}
	// 在等待完成列表没找到，则在完成列表匹配
	if( resultBool ) {
		count = musicInfoVector.size( );
		auto data = musicInfoVector.data( );
		qsizetype index = 0;
		for( ; index < count; index += 1 )
			if( data[ index ]->getMusicFilePath( ) == absFilePath ) {
				loadMusicFileMutex->unlock( );
				return false; // 已经在完成列表
			}
	}

	loadMusicFileMutex->unlock( );
	auto musicInfoItemWidget = new MusicInfoItemWidget( this );
	if( musicInfoItemWidget->init( music_file_path, music_name, music_singer, duration ) == false ) {
		delete musicInfoItemWidget;
		return false;
	}
	musicInfoItemWidget->parentPlayListWidget = this;
	loadMusicFileMutex->lock( );
	musicInfoVector.emplace_back( musicInfoItemWidget );
	loadMusicFileMutex->unlock( );
	return true;
}

bool PlayerListWidget::fromFileLoadItemInfo( const QString &music_file_path ) {
	QFileInfo fileInfo( music_file_path );
	bool resultBool = fileInfo.exists( );
	if( resultBool == false )
		return false; // 不存在
	auto absFilePath = fileInfo.absoluteFilePath( );
	loadMusicFileMutex->lock( );

	qsizetype count = loadMusicFileHistory.size( );
	if( count ) {
		qsizetype index = 0;
		auto data = loadMusicFileHistory.data( );
		for( ; index < count; index += 1 )
			if( data[ index ] == absFilePath ) {
				resultBool = false;
				break; // 存在
			}
	}
	// 在等待完成列表没找到，则在完成列表匹配
	if( resultBool ) {
		count = musicInfoVector.size( );
		if( count ) {
			auto data = musicInfoVector.data( );
			qsizetype index = 0;
			for( ; index < count; index += 1 )
				if( data[ index ]->getMusicFilePath( ) == absFilePath ) {
					resultBool = false;
					break; // 存在
				}
		}
	}
	// 都找不到，则加入等待列表
	if( resultBool )
		loadMusicFileHistory.append( absFilePath );
	loadMusicFileMutex->unlock( );
	// 这是找到了，所以退出
	if( resultBool == false )
		return false;

	// 开始工作
	QMediaPlayer *mediaPlayer = new QMediaPlayer;
	mediaPlayer->setSource( QUrl::fromLocalFile( absFilePath ) );
	connect( mediaPlayer, &QMediaPlayer::mediaStatusChanged, [mediaPlayer, this, absFilePath] ( QMediaPlayer::MediaStatus status ) {
		if( status != QMediaPlayer::LoadedMedia )
			return; // 没加载完成，则跳过 
		loadMusicFileMutex->lock( );

		qsizetype count = loadMusicFileHistory.size( );
		if( count ) {
			qsizetype index = 0;
			auto data = loadMusicFileHistory.data( );
			for( ; index < count; index += 1 )
				if( data[ index ] == absFilePath ) {
					loadMusicFileHistory.erase( loadMusicFileHistory.begin( ) + index );
					break; // 存在
				}
			count = loadMusicFileHistory.size( );
		}
		MusicInfoItemWidget *itemWidget = new MusicInfoItemWidget( this );
		musicInfoVector.emplace_back( itemWidget );
		loadMusicFileMutex->unlock( );
		QMediaMetaData mediaMetaData = mediaPlayer->metaData( );
		itemWidget->init( absFilePath, mediaMetaData );
		itemWidget->parentPlayListWidget = this;
		mediaPlayer->deleteLater( );
		if( count == 0 )
			updateItemWidget( );
	} );
	return true;
}

QVector< MusicInfoItemWidget * > & PlayerListWidget::getMusicInfoVector( QVector< MusicInfoItemWidget * > &result_vector ) const {
	loadMusicFileMutex->lock( );
	result_vector = musicInfoVector;
	loadMusicFileMutex->unlock( );
	return result_vector;
}

QVector< QString > & PlayerListWidget::getListMusicFile( QVector< QString > &result_vector ) const {
	loadMusicFileMutex->lock( );
	qsizetype count = musicInfoVector.size( );
	if( count == 0 ) {
		loadMusicFileMutex->unlock( );
		return result_vector;
	}
	result_vector.resize( count );
	auto copyToData = result_vector.data( );
	auto musicInfoData = musicInfoVector.data( );
	qsizetype index;
	for( index = 0; index < count; index += 1 )
		copyToData[ index ] = musicInfoData[ index ]->getMusicFilePath( );
	index = count;
	count = loadMusicFileHistory.size( );
	auto loadMusciFileHistoryData = loadMusicFileHistory.data( );
	qsizetype newSize = count + index;
	result_vector.resize( newSize );
	copyToData = result_vector.data( ) + index;
	for( index = 0; index < count; index += 1 )
		copyToData[ index ] = loadMusciFileHistoryData[ index ];
	loadMusicFileMutex->unlock( );
	return result_vector;
}

bool PlayerListWidget::renderMusicInfoItem( QImage &result_render_image, const MusicInfoItem *render_target ) const {
	loadMusicFileMutex->lock( );
	qsizetype count = musicInfoVector.size( );
	if( count == 0 ) {
		loadMusicFileMutex->unlock( );
		return false;
	}
	auto data = musicInfoVector.data( );
	qsizetype index;
	for( index = 0; index < count; index += 1 )
		if( render_target == data[ index ] ) {
			loadMusicFileMutex->unlock( );
			return false;
		}
	auto renderTarget = data[ index ];
	loadMusicFileMutex->unlock( );
	return renderAtMusicInfoItem( result_render_image, renderTarget );
}

bool PlayerListWidget::renderAtMusicInfoItem( QImage &result_render_image, MusicInfoItem *render_target ) const {
	return renderAtMusicInfoItem( result_render_image, render_target, splitWidth );
}

bool PlayerListWidget::renderAtMusicInfoItem( QImage &result_render_image, MusicInfoItem *render_target, int split_width ) const {
	auto appInstance = AppInstance::getAppInstance( );
	auto renderImage = appInstance->getRenderImage( );
	auto font = renderImage->getFont( );
	auto fontMetrics = renderImage->getFontMetrics( );
	int itemHeight = fontMetrics->height( );
	auto musicName = render_target->getMusicName( );
	auto musicSinger = render_target->getMusicSinger( );
	auto formatStringDuration = render_target->getFormatStringDuration( );
	int musicNameWidth = fontMetrics->horizontalAdvance( musicName );
	int musicSingerWidth = fontMetrics->horizontalAdvance( musicSinger );
	int formatStringDurationeWidth = fontMetrics->horizontalAdvance( formatStringDuration );
	return renderAtMusicInfoItem( result_render_image, render_target, itemHeight, split_width, musicNameWidth, musicSingerWidth, formatStringDurationeWidth, font );
}

void PlayerListWidget::doubleClickMusicItemWidget( MusicInfoItemWidget *double_target ) {
}

void PlayerListWidget::apendSelectMusicItemWidget( MusicInfoItemWidget *append_select_target ) {
	selectItemMutex->lock( );
	activeLeftItemWidget = append_select_target;
	selectLeftItemWidget = append_select_target;
	selectItemMutex->unlock( );
	auto appInstance = AppInstance::getAppInstance( );
	auto keyboardModifiers = ( Qt::KeyboardModifier ) appInstance->keyboardModifiers( ).toInt( );
	qsizetype count;
	switch( keyboardModifiers ) {
		case Qt::KeyboardModifier::ControlModifier : {
			QMutexLocker locker( selectItemMutex );
			qsizetype count = selectItemWidgetVector.size( );
			if( count ) {
				auto musicInfoItemWidget = selectItemWidgetVector.data( );
				qsizetype index = 0;
				for( ; index < count; index += 1 )
					if( musicInfoItemWidget[ index ] == append_select_target )
						break;
				if( index < count ) {
					count -= 1;
					for( ; index < count; index += 1 )
						musicInfoItemWidget[ index ] = musicInfoItemWidget[ index + 1 ];
					musicInfoItemWidget[ index ] = append_select_target; // 排序到末尾
					break;
				}
			}
			selectItemWidgetVector.emplace_back( append_select_target );
		}
		break;
		case Qt::KeyboardModifier::ShiftModifier : {
			QMutexLocker locker( selectItemMutex );
			count = selectItemWidgetVector.size( );
			if( count > 0 ) {
				QMutexLocker loadFileLocker( loadMusicFileMutex );
				auto selectItemWidgetData = selectItemWidgetVector.data( );
				auto findFirstItemWidth = selectItemWidgetData[ 0 ];
				qsizetype musicCount = musicInfoVector.size( );
				auto findSourceData = musicInfoVector.data( );
				qsizetype musicIndex = 0;
				// 匹配 getBegIndex
				for( ; musicIndex < musicCount; musicIndex += 1 )
					if( findSourceData[ musicIndex ] == findFirstItemWidth )
						break;
				if( musicIndex == musicCount )
					break;
				qsizetype getBegIndex = musicIndex;

				// 匹配 getEndIndex
				for( musicIndex = 0; musicIndex < musicCount; musicIndex += 1 )
					if( findSourceData[ musicIndex ] == append_select_target )
						break;
				if( musicIndex == musicCount )
					break;
				qsizetype getEndIndex = musicIndex;
				if( getEndIndex != getBegIndex ) {
					if( getEndIndex > getBegIndex ) {
						auto endIndex = getEndIndex + 1;
						count = endIndex - getBegIndex;
						selectItemWidgetVector.resize( count );
						selectItemWidgetData = selectItemWidgetVector.data( );
						findSourceData += getBegIndex;
						for( musicIndex = 0; musicIndex < endIndex; musicIndex += 1 )
							selectItemWidgetData[ musicIndex ] = findSourceData[ musicIndex ];
					} else {
						auto endIndex = getBegIndex + 1;
						count = endIndex - getEndIndex;
						selectItemWidgetVector.resize( count );
						selectItemWidgetData = selectItemWidgetVector.data( );
						findSourceData += getEndIndex;
						qint64 destIndex = count - 1;
						for( musicIndex = 0; musicIndex < endIndex; musicIndex += 1, destIndex -= 1 )
							selectItemWidgetData[ destIndex ] = findSourceData[ musicIndex ];
					}
				}
				break;
			}
			// 如果 count == 0，这继续运行 default，直到跳出 switch
		}
		default : {
			QMutexLocker locker( selectItemMutex );
			selectItemWidgetVector.resize( 1 );
			auto musicInfoItemWidget = selectItemWidgetVector.data( );
			musicInfoItemWidget[ 0 ] = append_select_target;
		}
	}
	QVector< MusicInfoItemWidget * > resultVector;
	getSelectItemWidgetVector( resultVector );
	emit itemSelect( resultVector );
	update( );
}

void PlayerListWidget::updateItemWidget( ) {
	int offsetY = 0;
	auto appInstance = AppInstance::getAppInstance( );
	auto renderImage = appInstance->getRenderImage( );
	auto fontMetrics = renderImage->getFontMetrics( );
	int height = fontMetrics->height( );
	auto newWidth = this->widgetBeforeWidth + this->widgetAfterWidth + this->splitWidth * 5 + this->musicNameWidth + this->musicSingerWidth + this->musicDurationWidth + this->indexWidth;
	loadMusicFileMutex->lock( );
	qsizetype count = musicInfoVector.size( );
	if( count == 0 ) {
		loadMusicFileMutex->unlock( );
		if( newWidth > 0 )
			setFixedWidth( newWidth );
		return;
	}
	auto data = musicInfoVector.data( );
	qsizetype index;
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
		itemWidget->setGeometry( 0, offsetY, newWidth, height );
		itemWidget->update( );
		itemWidget->show( );
		offsetY += height;
	}

	loadMusicFileMutex->unlock( );
	if( offsetY > 0 && newWidth > 0 )
		this->setFixedSize( newWidth, offsetY );
	else if( offsetY == 0 && newWidth > 0 )
		setFixedWidth( newWidth );
	else if( offsetY > 0 && newWidth == 0 )
		setFixedHeight( offsetY );
}

bool PlayerListWidget::renderAtMusicInfoItem( QImage &result_render_image, MusicInfoItem *render_target, int item_height, int split_width, int name_item_width, int singer_item_width, int duration_item_width, const QFont *item_font ) const {
	if( item_font == nullptr )
		return false;
	int imageWidth = split_width * 4 + name_item_width + singer_item_width + duration_item_width;
	QImage buff = QImage( imageWidth, item_height, QImage::Format_RGBA8888 );
	if( buff.isNull( ) )
		return false;
	buff.fill( 0 );
	int offsetSplitX = split_width / 2;
	QPainter painter;
	painter.begin( &buff );
	auto pen = painter.pen( );
	pen.setWidth( split_width );
	painter.setPen( pen );
	painter.setFont( *item_font );

	int drawOffsetX = offsetSplitX;
	QRect drawRect;

	painter.drawLine( drawOffsetX, 0, drawOffsetX, item_height );
	drawOffsetX += offsetSplitX;
	drawRect = QRect( QPoint( drawOffsetX, 0 ), QSize( name_item_width, item_height ) );
	painter.drawText( drawRect, render_target->musicName );
	drawOffsetX += name_item_width + offsetSplitX;

	painter.drawLine( drawOffsetX, 0, drawOffsetX, item_height );
	drawOffsetX += offsetSplitX;
	drawRect = QRect( QPoint( drawOffsetX, 0 ), QSize( musicSingerWidth, item_height ) );
	painter.drawText( drawRect, render_target->musicSinger );
	drawOffsetX += singer_item_width + offsetSplitX;

	painter.drawLine( drawOffsetX, 0, drawOffsetX, item_height );
	drawOffsetX += offsetSplitX;
	drawRect = QRect( QPoint( drawOffsetX, 0 ), QSize( duration_item_width, item_height ) );
	painter.drawText( drawRect, render_target->formatStringDuration );
	drawOffsetX += duration_item_width + offsetSplitX;

	painter.drawLine( drawOffsetX, 0, drawOffsetX, item_height );

	painter.end( );
	result_render_image = buff;
	return true;
}

void PlayerListWidget::paintEvent( QPaintEvent *event ) {
	QPainter painter;
	painter.begin( this );

	painter.setPen( *pen );

	QMutexLocker locker( selectItemMutex );
	qsizetype count = selectItemWidgetVector.size( );
	if( count ) {
		auto data = selectItemWidgetVector.data( );
		qsizetype index;
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
}

void PlayerListWidget::resizeEvent( QResizeEvent *event ) {
	auto size = event->size( );
	currentWidgetHeight = size.height( );
	currentWidgetWidth = size.width( );
	//repaint( );
}

void PlayerListWidget::mouseMoveEvent( QMouseEvent *event ) {
	loadMusicFileMutex->lock( );
	qsizetype count = musicInfoVector.size( );
	if( count == 0 ) {
		loadMusicFileMutex->unlock( );
		return;
	}
	auto point = event->pos( );
	auto data = musicInfoVector.data( );
	qsizetype index;
	for( index = 0; index < count; index += 1 )
		if( data[ index ]->geometry( ).contains( point ) ) {
			activeLeftItemWidget = data[ index ];
			break;
		}
	loadMusicFileMutex->unlock( );
	if( activeLeftItemWidget )
		update( );
}

void PlayerListWidget::mouseReleaseEvent( QMouseEvent *event ) {
	Qt::MouseButton mouseButton = event->button( );
	switch( mouseButton ) {
		case Qt::MouseButton::LeftButton : {
			MusicInfoItemWidget *selectItem = nullptr;
			MusicInfoItemWidget *doubleItemWidget = nullptr;
			loadMusicFileMutex->lock( );
			qsizetype count = musicInfoVector.size( );
			if( count == 0 ) {
				loadMusicFileMutex->unlock( );
				return;
			}
			auto point = event->pos( );
			auto data = musicInfoVector.data( );
			qsizetype index;
			for( index = 0; index < count; index += 1 )
				if( data[ index ]->geometry( ).contains( point ) ) {
					if( selectLeftItemWidget == data[ index ] ) {// 双击检测
						auto currentDateTime = QDateTime::currentDateTime( );
						auto milliseconds = currentDateTime - *beforeClickTime;
						if( doubleClickIntervalTimeMilliSecond > milliseconds.count( ) ) {
							doubleClickMusicItemWidget( data[ index ] );
							doubleItemWidget = data[ index ];
						}
						*beforeClickTime = currentDateTime;
						break;
					}
					selectItem = data[ index ];
					break;
				}
			loadMusicFileMutex->unlock( );
			if( selectItem )
				apendSelectMusicItemWidget( data[ index ] );
			if( doubleItemWidget )
				emit itemDoubleSelect( doubleItemWidget ); // 触发信号
		}
		break;
		case Qt::MouseButton::RightButton : {
			MusicInfoItemWidget *selectItem = nullptr;
			loadMusicFileMutex->lock( );
			qsizetype count = musicInfoVector.size( );
			if( count == 0 ) {
				loadMusicFileMutex->unlock( );
				return;
			}
			auto point = event->pos( );
			auto data = musicInfoVector.data( );
			qsizetype index;
			for( index = 0; index < count; index += 1 )
				if( data[ index ]->geometry( ).contains( point ) ) {
					selectItem = data[ index ];
					break;
				}
			loadMusicFileMutex->unlock( );
			if( selectItem ) {
				apendSelectMusicItemWidget( selectItem );
				playerWidgetMenu->exec( QCursor::pos( ) );
			}
		}
		break;
	}
}
