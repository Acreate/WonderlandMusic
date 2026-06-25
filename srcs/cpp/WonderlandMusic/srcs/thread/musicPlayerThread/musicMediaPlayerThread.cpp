#include "musicMediaPlayerThread.h"

#include <QAudioDevice>
#include <QAudioOutput>
#include <QFileInfo>
#include <QMediaPlayer>
#include <QMutex>

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
	isRunOver = true;
	bool stopPlayerMusic = MusicPlayerThread::stopPlayerMusic( );
	emit threadOver( );
	return stopPlayerMusic;
}

MusicMediaPlayerThread::MusicMediaPlayerThread( const QString &load_file_path ) : MusicPlayerThread( load_file_path ) {
	controlGepTime = 100;
}

MusicMediaPlayerThread::~MusicMediaPlayerThread( ) {
}

bool MusicMediaPlayerThread::playerThread( MusicPlayerThread *music_player_thread ) {
	emit threadStart( );
	mediaPlayer = new QMediaPlayer;
	audioOutput = new QAudioOutput;

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
