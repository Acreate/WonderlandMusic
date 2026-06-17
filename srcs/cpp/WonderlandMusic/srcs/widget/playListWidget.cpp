#include "playListWidget.h"

#include <QFileInfo>
#include <QJsonObject>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QUrl>
#include <qjsondocument.h>
#include <QMutex>

#include "../application/appInstance.h"
#include "../application/appTranslate.h"
#include "../application/jsonFileKey.h"

#include "../itemWidget/musicInfoItemWidget.h"

#include "../msgInfo/messageErrorOut.h"

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
}
bool PlayListWidget::loadJsonPathInfo( ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto jsonFileKey = appInstance->getJsonFileKey( );
	auto fileJsonPath = jsonFileKey->getMusicPlayerListInfoFileJsonPath( );
	QJsonObject fileJsonObject;
	if( PathTools::readJsonObject( fileJsonObject, fileJsonPath ) == false )
		return true;
	auto end = fileJsonObject.end( );
	auto find = fileJsonObject.find( jsonFileKey->getMusicInfoListCount( ) );
	if( end == find ) {
		Message_Error_Out << appInstance->getTranslate( )->getNotFindJsonKey( ) + " : " + jsonFileKey->getMusicInfoListCount( );
		return true;
	}

	qint64 count = find.value( ).toInteger( );

	QJsonObject subJsonObject;
	find = fileJsonObject.find( jsonFileKey->getMusicInfoListName( ) );
	if( end == find ) {
		Message_Error_Out << appInstance->getTranslate( )->getNotFindJsonKey( ) + " : " + jsonFileKey->getMusicInfoListCount( );
		return true;
	}
	subJsonObject = find.value( ).toObject( );
	auto foreachIterator = subJsonObject.begin( );
	auto foreachEnd = subJsonObject.end( );

	QVector< MusicInfoItemWidget * > buff( count, nullptr );
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
		auto ctreaItem = new MusicInfoItemWidget( );
		if( MusicInfoItemWidget::forJsonObject( *ctreaItem, musicInfoJsonObject ) == false ) {
			delete ctreaItem;
			continue;
		}
		ctreaItem->setParent( this );
		data[ converResultIndex ] = ctreaItem;
	}

	loadMusicFileMutex->lock( );
	auto oldCount = musicInfoVector.size( );
	QVector< MusicInfoItemWidget * > releaseVector( oldCount, nullptr );
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
	return true;
}
bool PlayListWidget::writeJsonPathInfo( ) {

	auto appInstance = AppInstance::getAppInstance( );
	auto jsonFileKey = appInstance->getJsonFileKey( );
	loadMusicFileMutex->lock( );
	qsizetype count = musicInfoVector.size( );
	if( count == 0 ) {
		loadMusicFileMutex->unlock( );
		return true;
	}
	auto sourceData = musicInfoVector.data( );
	QVector< MusicInfoItemWidget * > buff( count );
	auto destData = buff.data( );
	qsizetype index = 0;
	for( ; index < count; index += 1 )
		destData[ index ] = sourceData[ index ];
	loadMusicFileMutex->unlock( );

	QJsonObject fileJsonObject;
	fileJsonObject.insert( jsonFileKey->getMusicInfoListCount( ), count );

	QJsonObject arrayJsonObject;

	for( index = 0; index < count; index += 1 ) {
		QJsonObject subJsonObject;
		if( MusicInfoItemWidget::toJsonObect( subJsonObject, *destData[ index ] ) == false )
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
	auto musicInfoItemWidget = new MusicInfoItemWidget( );;
	if( musicInfoItemWidget->init( music_file_path, music_name, music_singer, duration ) == false ) {
		delete musicInfoItemWidget;
		return false;
	}
	musicInfoItemWidget->setParent( this );
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
		auto data = musicInfoVector.data( );
		qsizetype index = 0;
		for( ; index < count; index += 1 )
			if( data[ index ]->getMusicFilePath( ) == absFilePath ) {
				resultBool = false;
				break; // 存在
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

		}
		MusicInfoItemWidget *itemWidget = new MusicInfoItemWidget( );
		musicInfoVector.emplace_back( itemWidget );
		loadMusicFileMutex->unlock( );
		QMediaMetaData mediaMetaData = mediaPlayer->metaData( );
		itemWidget->init( absFilePath, mediaMetaData );
		itemWidget->setParent( this );
		mediaPlayer->deleteLater( );
	} );
	return true;
}
QVector< MusicInfoItemWidget * > PlayListWidget::getMusicInfoVector( ) const {
	loadMusicFileMutex->lock( );
	QVector< MusicInfoItemWidget * > result = musicInfoVector;
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
