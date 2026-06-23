#include "musicPlayerThread.h"

#include <qaudiobuffer.h>
#include <qaudioformat.h>

MusicPlayerThread::MusicPlayerThread( const std::vector< QAudioBuffer > &audio_buffer_vector ) : audioBufferVector( audio_buffer_vector ) {
}

MusicPlayerThread::~MusicPlayerThread( ) {
}

void MusicPlayerThread::stop( ) {
	isJuimp = true;
}

void MusicPlayerThread::run( ) {
	isJuimp = false;
	size_t count = audioBufferVector.size( );
	auto audioBufferData = audioBufferVector.data( );

	size_t index;
	for( index = 0; index < count; index += 1 ) {
		if( isJuimp )
			break;
		QAudioBuffer audioBuffer = audioBufferData[ index ];
		auto audioFormat = audioBuffer.format( );
		int sampleRate = audioFormat.sampleRate( );
		int bytesPerSample = audioFormat.bytesPerSample( );
		int channels = audioFormat.channelCount( );
		qsizetype frameByteSize = audioBuffer.sampleCount( );
		double samplesPerFrame = frameByteSize * 1000.0;
		samplesPerFrame = samplesPerFrame / bytesPerSample / channels / sampleRate;
		emit playerMusicFrame( this, audioBuffer );
		msleep( samplesPerFrame );
	}
	emit overPlayerMusic( this );
}
