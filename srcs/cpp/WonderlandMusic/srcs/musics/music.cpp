#include "music.h"
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QUrl>
#include <QImage>
#include <QDateTime>

#include "../applications/application.h"
#include "../applications/applicationInstance.h"

#include "../msgInfo/messageErrorOut.h"
Music::~Music( ) {
}
Music::Music( const QString &music_path ) :
	musicPath( music_path ) {

	QMediaPlayer mediaPlayer;
	mediaPlayer.setSource( QUrl::fromLocalFile( music_path ) );

	auto application = ApplicationInstance::getInstance( )->getApplication( );
	while( QMediaPlayer::LoadedMedia != mediaPlayer.mediaStatus( ) )
		application->processEvents( );

	auto mediaMetaData = mediaPlayer.metaData( );
	if( mediaMetaData.isEmpty( ) ) {
		MessageErrorOut( ) << QObject::tr( "没有匹配音频文件信息" ) << " : " << music_path;
		return;
	}

	musicName = mediaMetaData.value( QMediaMetaData::Title ).toString( );
	singer = mediaMetaData.value( QMediaMetaData::ContributingArtist ).toString( );
	duration_ms = mediaMetaData.value( QMediaMetaData::Duration ).toLongLong( );
}
