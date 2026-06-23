#include "musicPlayerThread.h"

#include <QAudioOutput>
#include <QBuffer>
#include <QAudioSink>
#include <QDateTime>
#include <QMediaDevices>
#include <qaudiobuffer.h>
#include <qaudioformat.h>

#include "../application/appInstance.h"

#include "../msgInfo/messageErrorOut.h"

MusicPlayerThread::MusicPlayerThread( const std::vector< QAudioBuffer > &audio_buffer_vector ) : audioBufferVector( audio_buffer_vector ) {
	currentThisPtr = this;
	audioSink = nullptr;
}

MusicPlayerThread::~MusicPlayerThread( ) {
	emit overPlayerMusic( currentThisPtr );
	currentThisPtr = nullptr;
	if( audioSink )
		audioSink->deleteLater( );
}

void MusicPlayerThread::stop( ) {
	isJuimp = true;
}

void MusicPlayerThread::run( ) {
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
	double samplesPerFrame = 1000.0 / audioFormat.sampleRate( );
	audioSink = new QAudioSink( audioDevice, audioFormat );
	audioSink->reset( );
	qint64 frameCount = audioBuffer.frameCount( );
	ulong sleepMS = samplesPerFrame * frameCount;
	audioSink->setBufferFrameCount( frameCount );
	audioSink->setVolume( 1.0 );
	// 获取播放路径
	ioAudioSinkDevice = audioSink->start( );

	emit playerMusicFrame( currentThisPtr, audioSink, ioAudioSinkDevice, audioBuffer );
	QDateTime time = QDateTime::currentDateTime( );
	size_t index;
	for( index = 1; index < count; index += 1 )
		if( isJuimp )
			break;
		else {
			msleep( sleepMS );
			audioBuffer = audioBufferData[ index ];
			emit playerMusicFrame( currentThisPtr, audioSink, ioAudioSinkDevice, audioBuffer );
		}
	audioSink->stop( );
}
