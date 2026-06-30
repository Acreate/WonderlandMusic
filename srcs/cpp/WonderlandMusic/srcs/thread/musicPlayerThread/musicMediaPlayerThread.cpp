#include "musicMediaPlayerThread.h"

#include <QAudioDevice>
#include <QAudioOutput>
#include <QFileInfo>
#include <QMediaPlayer>
#include <QMutex>

#include "../../application/appEventManage.h"
#include "../../application/appInstance.h"

bool MusicMediaPlayerThread::startPlayerTread( ) {
	isRunOver = false;
	return playerThread( this );
}

bool MusicMediaPlayerThread::stopPlayerMusic( ) {
	if( mediaPlayer ) {
		mediaPlayer->stop( );
		auto appInstance = AppInstance::getAppInstance( );
		while( mediaPlayer->isPlaying( ) )
			appInstance->processEvents( );
		delete mediaPlayer;
		delete audioOutput;
		mediaPlayer = nullptr;
		audioOutput = nullptr;
	}
	isRunOver = true;
	bool stopPlayerMusic = MusicPlayerThread::stopPlayerMusic( );

	MusicMediaPlayerThreadEventInfo inf;
	inf.eventSenderPtr = this;
	inf.event = MusicPlayerThreadEventInfo::EventType::Thread_Over;
	Emit_MusicMediaPlayerThread_Event( this, inf );
	return stopPlayerMusic;
}

MusicMediaPlayerThread::MusicMediaPlayerThread( const QString &load_file_path ) : MusicPlayerThread( load_file_path ) {
	controlGepTime = 100;
}

MusicMediaPlayerThread::~MusicMediaPlayerThread( ) {
}

bool MusicMediaPlayerThread::playerThread( MusicPlayerThread *music_player_thread ) {
	MusicMediaPlayerThreadEventInfo inf;
	inf.eventSenderPtr = this;
	inf.event = MusicPlayerThreadEventInfo::EventType::Thread_Start;
	Emit_MusicMediaPlayerThread_Event( this, inf );
	mediaPlayer = new QMediaPlayer;
	audioOutput = new QAudioOutput;
	connect( mediaPlayer, &QMediaPlayer::mediaStatusChanged, this, [this] ( QMediaPlayer::MediaStatus status ) {
		switch( status ) {
			case QMediaPlayer::LoadingMedia :
				break;
			case QMediaPlayer::LoadedMedia :
				break;
			case QMediaPlayer::StalledMedia :
				break;
			case QMediaPlayer::BufferingMedia :
				break;
			case QMediaPlayer::BufferedMedia :
				break;
			case QMediaPlayer::NoMedia :
			case QMediaPlayer::EndOfMedia :
			case QMediaPlayer::InvalidMedia : {
				delete mediaPlayer;
				delete audioOutput;
				mediaPlayer = nullptr;
				audioOutput = nullptr;
				isRunOver = true;

				MusicMediaPlayerThreadEventInfo inf;
				inf.eventSenderPtr = this;
				inf.event = MusicPlayerThreadEventInfo::EventType::Thread_Over;
				Emit_MusicMediaPlayerThread_Event( this, inf );
			}
			break;
		}
	}, Qt::QueuedConnection );
	audioOutput->setVolume( 1.0 );

	mediaPlayer->setAudioOutput( audioOutput );

	QFileInfo info( musicFilePath );
	if( info.exists( ) == false )
		return false;
	auto absoluteFilePath = info.absoluteFilePath( );
	auto fromLocalFile = QUrl::fromLocalFile( absoluteFilePath );
	mediaPlayer->setSource( fromLocalFile );

	mediaPlayer->play( );
	isJump = false;
	return true;
}
