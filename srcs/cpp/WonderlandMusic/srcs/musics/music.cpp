#include "music.h"
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QUrl>
#include <QAudioDecoder>
#include <QDateTime>
#include <QFileInfo>

#include "../applications/application.h"
#include "../applications/applicationInstance.h"

#include "../msgInfo/messageErrorOut.h"
Music::~Music( ) {
	delete audioDecoder;
	delete mediaPlayer;
	delete info;
	delete musicUrl;

}
Music::Music( ) {
	audioDecoder = new QAudioDecoder;
	mediaPlayer = new QMediaPlayer;
	info = new QFileInfo;
	musicUrl = new QUrl;
}
bool Music::loadFile( const QString &music_path ) {
	info->setFile( music_path );
	if( info->exists( ) == false ) {
		MessageErrorOut( ) << QObject::tr( "路径不存在音频文件" ) << " : " << music_path;
		return false;
	}
	*musicUrl = QUrl::fromLocalFile( music_path );

	audioDecoder->setSource( *musicUrl );
	if( audioDecoder->isSupported( ) == false ) {
		MessageErrorOut( ) << QObject::tr( "不支持该文件的解码" ) << " : " << music_path;
		return false;
	}

	mediaPlayer = new QMediaPlayer;
	mediaPlayer->setSource( *musicUrl );
	auto application = ApplicationInstance::getInstance( )->getApplication( );
	while( QMediaPlayer::LoadedMedia != mediaPlayer->mediaStatus( ) )
		application->processEvents( );

	auto mediaMetaData = mediaPlayer->metaData( );
	if( mediaMetaData.isEmpty( ) ) {
		MessageErrorOut( ) << QObject::tr( "没有匹配音频文件信息" ) << " : " << music_path;
		return false;
	}
	musicName = mediaMetaData.value( QMediaMetaData::Title ).toString( );
	singer = mediaMetaData.value( QMediaMetaData::ContributingArtist ).toString( );
	duration_ms = mediaMetaData.value( QMediaMetaData::Duration ).toLongLong( );
	return true;
}
