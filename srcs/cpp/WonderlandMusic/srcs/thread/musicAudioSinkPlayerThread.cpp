#include "musicAudioSinkPlayerThread.h"

#include <QAudioOutput>
#include <QAudioSink>
#include <QDateTime>
#include <QMediaDevices>
#include <qaudiobuffer.h>
#include <qaudioformat.h>

#include "../application/appInstance.h"

#include "../msgInfo/messageErrorOut.h"

MusicAudioSinkPlayerThread::MusicAudioSinkPlayerThread( const std::vector< QAudioBuffer > &audio_buffer_vector ) : audioBufferVector( audio_buffer_vector ) {
	currentThisPtr = this;
	audioSink = nullptr;
}

MusicAudioSinkPlayerThread::~MusicAudioSinkPlayerThread( ) {
	emit overPlayerMusic( currentThisPtr );
	currentThisPtr = nullptr;
	if( audioSink )
		audioSink->deleteLater( );
}

void MusicAudioSinkPlayerThread::stop( ) {
	isJuimp = true;
}

void MusicAudioSinkPlayerThread::run( ) {
	size_t count = audioBufferVector.size( );
	if( count == 0 ) {
		emit overPlayerMusic( this );
		return;
	}
	QAudioBuffer *audioBufferData = audioBufferVector.data( );
	// 获取播放格式
	QAudioBuffer audioBuffer = audioBufferData[ 0 ];
	QAudioFormat audioFormat = audioBuffer.format( );
	auto audioDevice = QMediaDevices::defaultAudioOutput( );
	if( !audioDevice.isFormatSupported( audioFormat ) ) {
		emit overPlayerMusic( this );
		return;
	}

	isJuimp = false;
	// 每帧
	audioSink = new QAudioSink( audioDevice, audioFormat );
	qint64 frameCount = audioBuffer.frameCount( );
	audioSink->setBufferFrameCount( frameCount );
	audioSink->setVolume( 1.0 );
	// 获取播放路径
	ioAudioSinkDevice = audioSink->start( );

	emit playerMusicFrame( currentThisPtr, audioSink, ioAudioSinkDevice, audioBuffer );
	size_t index;
	QDateTime pre = QDateTime::currentDateTime( );
	for( index = 1; index < count; index += 1 ) {
		qint64 duration = audioBuffer.duration( );
		usleep( duration );
		if( isJuimp )
			break;
		audioBuffer = audioBufferData[ index ];
		emit playerMusicFrame( currentThisPtr, audioSink, ioAudioSinkDevice, audioBuffer );
		pre = QDateTime::currentDateTime( );
	}
	audioSink->stop( );
}
