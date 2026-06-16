#include "playListWidget.h"

#include <QDir>
#include <QFileInfo>
#include <QJsonObject>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QUrl>
#include <qjsondocument.h>

#include "../application/appInstance.h"
#include "../application/appTranslate.h"
#include "../application/jsonFileKey.h"

#include "../itemWidget/musicInfoItemWidget.h"

#include "../msgInfo/messageErrorOut.h"

#include "../tools/dateTimeFormat.h"

void PlayListWidget::clearMusicInfoVector( ) {
	loadMusicFileMutex.lock( );
	auto count = musicInfoVector.size( );
	if( count ) {
		auto data = musicInfoVector.data( );
		decltype(count) index = 0;
		for( ; index < count; index += 1 )
			delete data[ index ];
		musicInfoVector.clear( );
	}
	loadMusicFileMutex.unlock( );
}
PlayListWidget::~PlayListWidget( ) {
	clearMusicInfoVector( );
}
PlayListWidget::PlayListWidget( QWidget *parent ) : QWidget( parent ) { }
bool PlayListWidget::loadJsonPathInfo( ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto jsonFileKey = appInstance->getJsonFileKey( );
	auto fileJsonPath = jsonFileKey->getMusicPlayerListInfoFileJsonPath( );
	QFileInfo info( fileJsonPath );
	if( info.exists( ) == false )
		return true;
	QFile file( fileJsonPath );
	if( file.open( QIODeviceBase::ReadOnly ) == false ) {
		Message_Error_Out << appInstance->getTranslate( )->getReadFileError( ) + " : " + fileJsonPath;
		return true;
	}

	auto byteArray = file.readAll( );
	QJsonParseError parseError;
	auto jsonDocument = QJsonDocument::fromJson( byteArray, &parseError );
	if( parseError.error != QJsonParseError::NoError ) {
		Message_Error_Out << appInstance->getTranslate( )->getFileConverJsonDocError( ) + " : " + fileJsonPath;
		return true;
	}
	auto object = jsonDocument.object( );
	auto end = object.end( );
	auto find = object.find( jsonFileKey->getMusicInfoListCount( ) );
	if( end == find ) {
		Message_Error_Out << appInstance->getTranslate( )->getNotFindJsonKey( ) + " : " + jsonFileKey->getMusicInfoListCount( );
		return true;
	}

	qint64 count = find.value( ).toInteger( );

	QJsonObject subJsonObject;
	find = object.find( jsonFileKey->getMusicInfoListName( ) );
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

	loadMusicFileMutex.lock( );
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
	loadMusicFileMutex.unlock( );

	for( maxIndex = 0; maxIndex < oldCount; maxIndex += 1 )
		delete buffToData[ maxIndex ];
	return true;
}
bool PlayListWidget::writeJsonPathInfo( ) {

	auto appInstance = AppInstance::getAppInstance( );
	auto jsonFileKey = appInstance->getJsonFileKey( );
	loadMusicFileMutex.lock( );
	qsizetype count = musicInfoVector.size( );
	if( count == 0 ) {
		loadMusicFileMutex.unlock( );
		return true;
	}
	auto sourceData = musicInfoVector.data( );
	QVector< MusicInfoItemWidget * > buff( count );
	auto destData = buff.data( );
	qsizetype index = 0;
	for( ; index < count; index += 1 )
		destData[ index ] = sourceData[ index ];
	loadMusicFileMutex.unlock( );

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
	QFileInfo info( fileJsonPath );
	if( info.exists( ) == false ) {
		QDir dir = info.dir( );
		auto absolutePathDir = dir.absolutePath( );
		if( dir.exists( absolutePathDir ) == false )
			if( dir.mkdir( absolutePathDir ) == false ) {
				Message_Error_Out << appInstance->getTranslate( )->getCreateDirError( ) + " : " + absolutePathDir;
				return true;
			}
	}
	QFile file( fileJsonPath );
	if( file.open( QIODeviceBase::ReadOnly ) == false ) {
		Message_Error_Out << appInstance->getTranslate( )->getWriteFileError( ) + " : " + fileJsonPath;
		return true;
	}
	QJsonDocument writeJsonDocument( fileJsonObject );
	auto byteArray = writeJsonDocument.toJson( );
	file.write( byteArray );
	return true;
}
bool PlayListWidget::appendItem( const QString &music_file_path, const QString &music_name, const QString &music_singer, const qint64 &duration ) {

	QFileInfo fileInfo( music_file_path );
	bool resultBool = true;
	auto absFilePath = fileInfo.absoluteFilePath( );
	loadMusicFileMutex.lock( );

	qsizetype count = loadMusicFileHistory.size( );
	if( count ) {
		qsizetype index = 0;
		auto data = loadMusicFileHistory.data( );
		for( ; index < count; index += 1 )
			if( data[ index ] == absFilePath ) {
				loadMusicFileMutex.unlock( );
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

				loadMusicFileMutex.unlock( );
				return false; // 已经在完成列表
			}

	}

	loadMusicFileMutex.unlock( );
	auto musicInfoItemWidget = new MusicInfoItemWidget( );;
	if( musicInfoItemWidget->init( music_file_path, music_name, music_singer, duration ) == false ) {
		delete musicInfoItemWidget;
		return false;
	}
	musicInfoItemWidget->setParent( this );
	loadMusicFileMutex.lock( );
	musicInfoVector.emplace_back( musicInfoItemWidget );
	loadMusicFileMutex.unlock( );
	return true;
}
bool PlayListWidget::fromFileLoadItemInfo( const QString &music_file_path ) {
	QFileInfo fileInfo( music_file_path );
	bool resultBool = fileInfo.exists( );
	if( resultBool == false )
		return false; // 不存在
	auto absFilePath = fileInfo.absoluteFilePath( );
	loadMusicFileMutex.lock( );

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
	loadMusicFileMutex.unlock( );
	// 这是找到了，所以退出
	if( resultBool == false )
		return false;

	// 开始工作
	QMediaPlayer *mediaPlayer = new QMediaPlayer;
	mediaPlayer->setSource( QUrl::fromLocalFile( absFilePath ) );
	connect( mediaPlayer, &QMediaPlayer::mediaStatusChanged, [mediaPlayer, this, absFilePath] ( QMediaPlayer::MediaStatus status ) {
		if( status != QMediaPlayer::LoadedMedia )
			return; // 没加载完成，则跳过 
		loadMusicFileMutex.lock( );

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
		loadMusicFileMutex.unlock( );
		QMediaMetaData mediaMetaData = mediaPlayer->metaData( );
		itemWidget->init( absFilePath, mediaMetaData );
		itemWidget->setParent( this );
		mediaPlayer->deleteLater( );
	} );
	return true;
}
