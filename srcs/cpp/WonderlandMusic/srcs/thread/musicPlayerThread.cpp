#include "musicPlayerThread.h"

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
	if( audioSink ) {
		audioSink->stop( );
		audioSink->deleteLater( );
	}
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
	auto audioBufferData = audioBufferVector.data( );
	// 获取播放格式
	QAudioBuffer audioBuffer = audioBufferData[ 0 ];
	QAudioFormat audioFormat = audioBuffer.format( );
	auto audioDevice = QMediaDevices::defaultAudioOutput( );
	if( !audioDevice.isFormatSupported( audioFormat ) ) {
		Message_Error_Out << audioDevice.description( ) << " : " << "并不支持该格式";
		return;
	}

	isJuimp = false;

	// 创建播放对象
	if( audioSink ) {
		audioSink->stop( );
		audioSink->reset( );
		delete audioSink;
	}
	qsizetype sampleCount = audioBuffer.sampleCount( );
	int channelCount = audioFormat.channelCount( );
	int sampleRate = audioFormat.sampleRate( );
	double samplesPerFrame = sampleCount * 1000.0 / channelCount / sampleRate;

	//qsizetype frameByteSize = audioBuffer.sampleCount( );

	audioSink = new QAudioSink( audioDevice, audioFormat );
	audioSink->setBufferSize( sampleRate * 100 * sampleCount / 1000 );
	audioSink->setVolume( 0.5 );
	// 获取播放路径
	ioAudioSinkDevice = audioSink->start( );

	emit playerMusicFrame( currentThisPtr, audioSink, ioAudioSinkDevice, audioBuffer );
	QDateTime time = QDateTime::currentDateTime( );
	size_t index;
	for( index = 1; index < count; index += 1 )
		if( isJuimp )
			break;
		else {
			msleep( samplesPerFrame );
			if( isJuimp )
				break;
			audioBuffer = audioBufferData[ index ];
			emit playerMusicFrame( currentThisPtr, audioSink, ioAudioSinkDevice, audioBuffer );
		}
}
