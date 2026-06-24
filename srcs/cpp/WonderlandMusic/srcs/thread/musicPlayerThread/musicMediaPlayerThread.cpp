#include "musicMediaPlayerThread.h"

#include <QAudioDevice>
#include <QAudioOutput>
#include <QFileInfo>
#include <QMediaPlayer>

#include "../../application/appInstance.h"

bool MusicMediaPlayerThread::initVar( ) {
	if( mediaPlayer )
		return true;
	mediaPlayer = new QMediaPlayer;
	audioOutput = new QAudioOutput( );
	audioOutput->setVolume( 1.0 );

	mediaPlayer->setAudioOutput( audioOutput );
	return true;
}

bool MusicMediaPlayerThread::initSource( ) {
	QFileInfo info( musicFilePath );
	if( info.exists( ) == false )
		return false;
	auto absoluteFilePath = info.absoluteFilePath( );
	auto fromLocalFile = QUrl::fromLocalFile( absoluteFilePath );
	mediaPlayer->setSource( fromLocalFile );
	return true;
}

bool MusicMediaPlayerThread::initConnectSignals( ) {
	return true;
}

bool MusicMediaPlayerThread::initStartStatus( ) {
	mediaPlayer->play( );
	isJump = false;
	return true;
}

MusicMediaPlayerThread::MusicMediaPlayerThread( const QString &load_file_path ) : MusicPlayerThread( load_file_path ) {
	controlGepTime = 100;
}

MusicMediaPlayerThread::~MusicMediaPlayerThread( ) {
	if( mediaPlayer )
		delete mediaPlayer;
	if( audioOutput )
		delete audioOutput;
}

bool MusicMediaPlayerThread::startPlayerMusic( ) {
	MusicPlayerThread::startPlayerMusic( );
	return true;
}

bool MusicMediaPlayerThread::stopPlayerMusic( ) {
	isJump = true;
	return true;
}

bool MusicMediaPlayerThread::setPlayerMusicPosition( qint64 position ) {
	mediaPlayer->setPosition( position );
	return true;
}

bool MusicMediaPlayerThread::setPlayerMusicDuration( qint64 duration ) {
	return false;
}

bool MusicMediaPlayerThread::playerThread( MusicPlayerThread *music_player_thread ) {
	if( initVar( ) == false )
		return false;
	if( initSource( ) == false )
		return false;
	if( initConnectSignals( ) == false )
		return false;
	if( initStartStatus( ) == false )
		return false;
	auto appInstance = AppInstance::getAppInstance( );
	auto currentThread = QThread::currentThread( );
	do {
		emit durationChanged( mediaPlayer->duration( ) );
		emit durationChanged( mediaPlayer->position( ) );
		currentThread->msleep( controlGepTime );
		appInstance->processEvents( );
	} while( isJump == false );
	mediaPlayer->stop( );
	return true;
}
