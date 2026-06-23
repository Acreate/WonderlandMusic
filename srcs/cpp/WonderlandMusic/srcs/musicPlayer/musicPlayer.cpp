#include "musicPlayer.h"

#include <QAudioSink>
#include <QMediaPlayer>
#include <QIODevice>
#include <QAudioOutput>
#include <QAudioDevice>
#include <QMediaDevices>
#include <QFileInfo>
#include <QAudioDecoder>

#include "musicDecode.h"

#include "../application/appInstance.h"

#include "../msgInfo/messageErrorOut.h"

#include "../thread/musicPlayerThread.h"

#include "../tools/autoMakePtrTools.h"

#define  d_r( ptr ) if(ptr) (delete ptr, ptr = nullptr)

void MusicPlayer::deleteResource( ) {
	d_r( audioSink );
	d_r( musicDecode );
}

void MusicPlayer::playerMusicFrame( MusicPlayerThread *music_player_thread, const QAudioBuffer &audio_buffer ) {
	if( isPlayerMisucFile == false ) {
		music_player_thread->stop( );
		return;
	}
	if( audioSink == nullptr ) {
		audioSink = new QAudioSink( audio_buffer.format( ) );
		audioSink->setVolume( 1.0 );
		ioAudioSinkDevice = audioSink->start( );
	}
	auto constData = audio_buffer.constData< char >( );
	qsizetype byteCount = audio_buffer.byteCount( );
	ioAudioSinkDevice->write( constData, byteCount );
}

void MusicPlayer::overPlayerMusic( MusicPlayerThread *music_player_thread ) {
	music_player_thread->deleteLater( );
	if( audioSink ) {
		delete audioSink;
		audioSink = nullptr;
		ioAudioSinkDevice = nullptr;
	}
}

MusicPlayer::MusicPlayer( QObject *parent ) : QObject( parent ) {
}

bool MusicPlayer::init( ) {
	deleteResource( );
	isPlayerMisucFile = false;
	musicDecode = new MusicDecode;
	if( musicDecode->init( ) == false )
		return false;
	connect( musicDecode, &MusicDecode::finished_Signal, [this] ( const std::vector< QAudioBuffer > &audio_buffer_vector ) {
		auto musicPlayerThread = new MusicPlayerThread( audio_buffer_vector );
		connect( musicPlayerThread, &MusicPlayerThread::playerMusicFrame, this, &MusicPlayer::playerMusicFrame );
		connect( musicPlayerThread, &MusicPlayerThread::overPlayerMusic, this, &MusicPlayer::overPlayerMusic );
		isPlayerMisucFile = true;
		musicPlayerThread->start( );
	} );
	connect( musicDecode, &MusicDecode::error_Signal, [] ( MusicDecode::Error error, const QString &error_msg ) {
	} );
	return true;
}

bool MusicPlayer::playerMusic( const QString &music_file ) {
	QFileInfo loadMusicFileInfo( music_file );
	if( loadMusicFileInfo.exists( ) == false )
		return false;
	if( isPlayerMisucFile ) {
		auto appInstance = AppInstance::getAppInstance( );
		while( isPlayerMisucFile )
			appInstance->processEvents( );
	}
	if( musicDecode->isDecoding( ) )
		musicDecode->stop( );
	musicDecode->setSource( music_file );
	musicDecode->start( );
	return true;
}
