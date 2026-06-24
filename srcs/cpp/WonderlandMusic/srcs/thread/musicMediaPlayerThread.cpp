#include "musicMediaPlayerThread.h"

#include <QAudioDevice>
#include <QAudioOutput>
#include <QFileInfo>
#include <QMediaPlayer>

#include "../application/appInstance.h"

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
	QFileInfo info( load_file_path );
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

MusicMediaPlayerThread::MusicMediaPlayerThread( const QString &load_file_path ) : load_file_path( load_file_path ) {
}

MusicMediaPlayerThread::~MusicMediaPlayerThread( ) {
	if( mediaPlayer )
		delete mediaPlayer;
	if( audioOutput )
		delete audioOutput;
}

void MusicMediaPlayerThread::stop( ) {
	isJump = true;
}

void MusicMediaPlayerThread::run( ) {
	if( initVar( ) == false )
		return;
	if( initSource( ) == false )
		return;
	if( initConnectSignals( ) == false )
		return;
	if( initStartStatus( ) == false )
		return;
	auto appInstance = AppInstance::getAppInstance( );
	do {
		emit durationChanged( mediaPlayer->duration( ) );
		emit durationChanged( mediaPlayer->position( ) );
		msleep( 1000 );
		appInstance->processEvents( );
	} while( isJump == false );
	mediaPlayer->stop( );
}
