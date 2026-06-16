#include "playListWidget.h"

#include <QFileInfo>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QUrl>

#include "../tools/dateTimeFormat.h"

MusicInfo::MusicInfo( const QString &file_path, const QMediaMetaData &mediaMetaData ) {
	musicName = mediaMetaData.stringValue( QMediaMetaData::Title );
	musicSinger = mediaMetaData.stringValue( QMediaMetaData::ContributingArtist );
	if( musicSinger.isEmpty( ) )
		musicSinger = mediaMetaData.stringValue( QMediaMetaData::AlbumArtist );
	if( musicSinger.isEmpty( ) )
		musicSinger = mediaMetaData.stringValue( QMediaMetaData::Author );
	duration = mediaMetaData.value( QMediaMetaData::Duration ).toLongLong( );
	formatStringDuration = DateTimeFormat::millsecondToHourMinSecFrom( duration );
}
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
	return false; // todo : 加载 json 文件
}
bool PlayListWidget::writeJsonPathInfo( ) {
	return false; // todo : 写入 json 文件
}
bool PlayListWidget::appendItem( const QString &music_file_path, const QString &music_name, const QString &music_singer, const qint64 &duration ) {
	return false;
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
		QMediaMetaData mediaMetaData = mediaPlayer->metaData( );
		musicInfoVector.emplace_back( new MusicInfo( absFilePath, mediaMetaData ) );
		loadMusicFileMutex.unlock( );
		mediaPlayer->deleteLater( );
	} );
	return false;
}
