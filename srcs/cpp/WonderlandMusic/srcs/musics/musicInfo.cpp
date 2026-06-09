#include "musicInfo.h"

#include <QAudioDecoder>
#include <QFileInfo>
#include <QMediaMetaData>
#include <QMediaPlayer>

#include "../applications/applicationInstance.h"

#include "../msgInfo/messageErrorOut.h"
bool MusicInfo::open( const QString &file_path ) {
	auto application = ApplicationInstance::getApplicationInstance( );
	if( application->musicFileNmaeSupperDecoder( file_path ) == false ) {
		//MessageErrorOut( ) << QObject::tr( "音频文件后缀不匹配" ) << " : " << file_path;
		return false;
	}
	QFileInfo info( file_path );
	QString absoluteFilePath = info.absoluteFilePath( );
	if( info.exists( ) == false ) {
		//MessageErrorOut( ) << QObject::tr( "路径不存在音频文件" ) << " : " << absoluteFilePath;
		return false;
	}
	musicUrl = QUrl::fromLocalFile( absoluteFilePath );
	QMediaPlayer mediaPlayer;
	mediaPlayer.setSource( musicUrl );
	QMediaPlayer::MediaStatus mediaStatus = mediaPlayer.mediaStatus( );
	if( mediaStatus == QMediaPlayer::NoMedia ) {
		//MessageErrorOut( ) << QObject::tr( "加载的音频文件异常" ) << " : " << absoluteFilePath;
		return false;
	}
	for( ; QMediaPlayer::LoadedMedia != mediaStatus; mediaStatus = mediaPlayer.mediaStatus( ) )
		if( application->getQuitStatus( ) == true )
			return false;
		else
			application->processEvents( );

	auto mediaMetaData = mediaPlayer.metaData( );
	if( mediaMetaData.isEmpty( ) ) {
		//MessageErrorOut( ) << QObject::tr( "没有匹配音频文件信息" ) << " : " << absoluteFilePath;
		return false;
	}
	musicName = mediaMetaData.value( QMediaMetaData::Title ).toString( );
	singer = mediaMetaData.value( QMediaMetaData::ContributingArtist ).toString( );
	duration_ms = mediaMetaData.value( QMediaMetaData::Duration ).toLongLong( );
	return true;
}
