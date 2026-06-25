#include "musicMediaPlayerThread.h"

#include <QAudioDevice>
#include <QAudioOutput>
#include <QFileInfo>
#include <QMediaPlayer>

#include "../../application/appInstance.h"

MusicMediaPlayerThread::MusicMediaPlayerThread( const QString &load_file_path ) : MusicPlayerThread( load_file_path ) {
	controlGepTime = 100;
}

MusicMediaPlayerThread::~MusicMediaPlayerThread( ) {
}

bool MusicMediaPlayerThread::setPlayerMusicPosition( qint64 position ) {
	isSetPos = true;
	this->pos = position;
	return true;
}

bool MusicMediaPlayerThread::setPlayerMusicDuration( qint64 duration ) {
	return false;
}

bool MusicMediaPlayerThread::playerThread( MusicPlayerThread *music_player_thread ) {
	QMediaPlayer *mediaPlayer = new QMediaPlayer;
	QAudioOutput *audioOutput = new QAudioOutput;

	connect( mediaPlayer, &QMediaPlayer::destroyed, [mediaPlayer] ( QObject *release_ptr ) {
		bool cond = release_ptr == mediaPlayer;
	} );

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

	auto appInstance = AppInstance::getAppInstance( );
	auto currentThread = QThread::currentThread( );
	do {
		emit durationChanged( mediaPlayer->duration( ) );
		emit durationChanged( mediaPlayer->position( ) );
		currentThread->msleep( controlGepTime );
		appInstance->processEvents( );
		if( isSetPos ) {
			isSetPos = false;
			mediaPlayer->setPosition( this->pos );
		}
	} while( isJump == false );
	mediaPlayer->stop( );
	do
		appInstance->processEvents( );
	while( mediaPlayer->isPlaying( ) );
	mediaPlayer->setAudioOutput( nullptr );
	delete audioOutput;
	mediaPlayer->deleteLater( );
	appInstance->processEvents( );
	return true;
}
