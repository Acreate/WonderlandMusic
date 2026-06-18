#include "playListWidget.h"

#include <QPaintEvent>
#include <QJsonObject>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QUrl>
#include <QMutex>
#include <QPainter>
#include <QThread>

#include "playerListTopWidget.h"

#include "../application/appInstance.h"
#include "../application/appTranslate.h"
#include "../application/jsonFileKey.h"
#include "../application/renderImage.h"

#include "../item/musicInfoItem.h"

#include "../itemWidget/musicInfoItemWidget.h"

#include "../msgInfo/messageErrorOut.h"

#include "../thread/widgetThread.h"

#include "../tools/pathTools.h"

void PlayListWidget::clearMusicInfoVector( ) {
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

PlayListWidget::~PlayListWidget( ) {
	clearMusicInfoVector( );
	delete loadMusicFileMutex;
}

PlayListWidget::PlayListWidget( QWidget *parent ) : QWidget( parent ) {
	loadMusicFileMutex = new QMutex;
	splitWidth = musicNameWidth = musicSingerWidth = musicDurationWidth = 4;
	updateItemWidget( );
}

void PlayListWidget::setItemWidth( const PlayerListTopWidget *player_list_top_widget ) {
	int widgetBeforeWidth = player_list_top_widget->getWidgetBeforeWidth( );
	int splitWidth = player_list_top_widget->getSplitWidth( );
	int musicNameWidth = player_list_top_widget->getMusicNameWidth( );
	int musicSingerWidth = player_list_top_widget->getMusicSingerWidth( );
	int musicDurationWidth = player_list_top_widget->getMusicDurationWidth( );
	int widgetAfterWidth = player_list_top_widget->getWidgetAfterWidth( );
	setItemWidth( widgetBeforeWidth, splitWidth, musicNameWidth, musicSingerWidth, musicDurationWidth, widgetAfterWidth );
}

void PlayListWidget::setItemWidth( int widget_before_width, int splite_width, int music_name_width, int music_singer_width, int music_duration_width, int widget_after_width ) {
	widgetBeforeWidth = widget_before_width;
	splitWidth = splite_width;
	musicNameWidth = music_name_width;
	musicSingerWidth = music_singer_width;
	musicDurationWidth = music_duration_width;
	widgetAfterWidth = widget_after_width;
	updateItemWidget( );
}

int PlayListWidget::getSplitWidth( ) const {
	return splitWidth;
}

void PlayListWidget::setSplitWidth( const int split_width ) {
	splitWidth = split_width;
	updateItemWidget( );
}

int PlayListWidget::getMusicNameWidth( ) const {
	return musicNameWidth;
}

void PlayListWidget::setMusicNameWidth( const int music_name_width ) {
	musicNameWidth = music_name_width;
	updateItemWidget( );
}

int PlayListWidget::getMusicSingerWidth( ) const {
	return musicSingerWidth;
}

void PlayListWidget::setMusicSingerWidth( const int music_singer_width ) {
	musicSingerWidth = music_singer_width;
	updateItemWidget( );
}

int PlayListWidget::getMusicDurationWidth( ) const {
	return musicDurationWidth;
}

void PlayListWidget::setMusicDurationWidth( const int format_string_duration_width ) {
	musicDurationWidth = format_string_duration_width;
	updateItemWidget( );
}

bool PlayListWidget::loadJsonPathInfo( ) {
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

bool PlayListWidget::writeJsonPathInfo( ) {
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

bool PlayListWidget::appendItem( const QString &music_file_path, const QString &music_name, const QString &music_singer, const qint64 &duration ) {
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

bool PlayListWidget::fromFileLoadItemInfo( const QString &music_file_path ) {
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

QVector< MusicInfoItemWidget * > PlayListWidget::getMusicInfoVector( ) const {
	loadMusicFileMutex->lock( );
	decltype(musicInfoVector) result = musicInfoVector;
	loadMusicFileMutex->unlock( );
	return result;
}

QVector< QString > PlayListWidget::getListMusicFile( ) const {
	QVector< QString > result;
	loadMusicFileMutex->lock( );
	qsizetype count = musicInfoVector.size( );
	result.resize( count );
	auto copyToData = result.data( );
	auto musicInfoData = musicInfoVector.data( );
	qsizetype index;
	for( index = 0; index < count; index += 1 )
		copyToData[ index ] = musicInfoData[ index ]->getMusicFilePath( );
	index = count;
	count = loadMusicFileHistory.size( );
	auto loadMusciFileHistoryData = loadMusicFileHistory.data( );
	qsizetype newSize = count + index;
	result.resize( newSize );
	copyToData = result.data( ) + index;
	for( index = 0; index < count; index += 1 )
		copyToData[ index ] = loadMusciFileHistoryData[ index ];
	loadMusicFileMutex->unlock( );
	return result;
}

bool PlayListWidget::renderMusicInfoItem( QImage &result_render_image, const MusicInfoItem *render_target ) const {
	loadMusicFileMutex->lock( );
	qsizetype count = musicInfoVector.size( );
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

bool PlayListWidget::renderAtMusicInfoItem( QImage &result_render_image, MusicInfoItem *render_target ) const {
	return renderAtMusicInfoItem( result_render_image, render_target, splitWidth );
}

bool PlayListWidget::renderAtMusicInfoItem( QImage &result_render_image, MusicInfoItem *render_target, int split_width ) const {
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

void PlayListWidget::updateItemWidget( ) {
	int offsetY = 0;
	auto appInstance = AppInstance::getAppInstance( );
	auto renderImage = appInstance->getRenderImage( );
	auto fontMetrics = renderImage->getFontMetrics( );
	int height = fontMetrics->height( );
	auto newWidth = this->widgetBeforeWidth + this->widgetAfterWidth + this->splitWidth * 4 + this->musicNameWidth + this->musicSingerWidth + this->musicDurationWidth;
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

bool PlayListWidget::renderAtMusicInfoItem( QImage &result_render_image, MusicInfoItem *render_target, int item_height, int split_width, int name_item_width, int singer_item_width, int duration_item_width, const QFont *item_font ) const {
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

void PlayListWidget::paintEvent( QPaintEvent *event ) {
}

void PlayListWidget::resizeEvent( QResizeEvent *event ) {
	auto size = event->size( );
	currentWidgetHeight = size.height( );
	currentWidgetWidth = size.width( );
	//repaint( );
}
