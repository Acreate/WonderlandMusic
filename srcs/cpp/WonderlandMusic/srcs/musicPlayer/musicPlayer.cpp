#include "musicPlayer.h"

#include <QAudioSink>
#include <QMediaPlayer>
#include <QIODevice>
#include <QAudioOutput>
#include <QAudioDevice>
#include <QMediaDevices>
#include <QFileInfo>
#include <QAudioDecoder>

#include "../tools/autoMakePtrTools.h"

#define  d_r( ptr ) if(ptr) (delete ptr, ptr = nullptr)

void MusicPlayer::deleteResource( ) {
	d_r( audioSink );
	d_r( audioDecoder );
}

void MusicPlayer::bufferReady( ) {
	QAudioBuffer audioBuffer = audioDecoder->read( );
	auto constData = audioBuffer.constData< char >( );
	ioDevice->write( constData, audioBuffer.byteCount( ) );
}

void MusicPlayer::finished( ) {
	delete audioSink;
	audioSink = nullptr;
}

void MusicPlayer::formatChanged( const QAudioFormat &fmt ) {
	audioSink = new QAudioSink( fmt );
	audioSink->setVolume( 1.0 );
	ioDevice = audioSink->start( );
}

MusicPlayer::MusicPlayer( QObject *parent ) : QObject( parent ) {
}

bool MusicPlayer::init( ) {
	deleteResource( );
	audioDecoder = new QAudioDecoder;
	return true;
}

bool MusicPlayer::playerMusic( const QString &music_file ) {
	QFileInfo loadMusicFileInfo( music_file );
	if( loadMusicFileInfo.exists( ) == false )
		return false;
	musicFilePath = loadMusicFileInfo.absoluteFilePath( );
	audioDecoder->setSource( QUrl::fromLocalFile( music_file ) );
	audioDecoder->start( );
	return true;
}
