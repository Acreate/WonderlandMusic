#include "musicAudioSinkPlayerThread.h"

#include <QAudioOutput>
#include <QAudioSink>
#include <QDateTime>
#include <QMediaDevices>
#include <qaudiobuffer.h>
#include <qaudioformat.h>

MusicAudioSinkPlayerThread::MusicAudioSinkPlayerThread( const QString &load_music_file ) : MusicPlayerThread( load_music_file ) {
}

MusicAudioSinkPlayerThread::~MusicAudioSinkPlayerThread( ) {
	if( audioSink )
		audioSink->deleteLater( );
}

bool MusicAudioSinkPlayerThread::stopPlayerMusic( ) {
	isJump = true;
	return false;
}

bool MusicAudioSinkPlayerThread::setPlayerMusicPosition( qint64 position ) {
	return false;
}

bool MusicAudioSinkPlayerThread::setPlayerMusicDuration( qint64 duration ) {
	return false;
}

bool MusicAudioSinkPlayerThread::playerThread( MusicPlayerThread *music_player_thread ) {
	size_t count = audioBufferVector.size( );
	if( count == 0 ) {
		emit overPlayerMusic( this );
		return false;
	}
	QAudioBuffer *audioBufferData = audioBufferVector.data( );
	// 获取播放格式
	QAudioBuffer audioBuffer = audioBufferData[ 0 ];
	QAudioFormat audioFormat = audioBuffer.format( );
	auto audioDevice = QMediaDevices::defaultAudioOutput( );
	if( !audioDevice.isFormatSupported( audioFormat ) ) {
		emit overPlayerMusic( this );
		return false;
	}

	isJump = false;
	// 每帧
	audioSink = new QAudioSink( audioDevice, audioFormat );
	qint64 frameCount = audioBuffer.frameCount( );
	audioSink->setBufferFrameCount( frameCount );
	audioSink->setVolume( 1.0 );
	// 获取播放路径
	ioAudioSinkDevice = audioSink->start( );
	auto currentThread = QThread::currentThread( );
	emit playerMusicFrame( this, audioSink, ioAudioSinkDevice, audioBuffer );
	size_t index;
	QDateTime pre = QDateTime::currentDateTime( );
	for( index = 1; index < count; index += 1 ) {
		qint64 duration = audioBuffer.duration( );
		currentThread->usleep( duration );
		if( isJump )
			break;
		audioBuffer = audioBufferData[ index ];
		emit playerMusicFrame( this, audioSink, ioAudioSinkDevice, audioBuffer );
		pre = QDateTime::currentDateTime( );
	}
	audioSink->stop( );
	return true;
}
