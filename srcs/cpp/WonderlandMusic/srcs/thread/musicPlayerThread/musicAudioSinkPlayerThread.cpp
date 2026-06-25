#include "musicAudioSinkPlayerThread.h"

#include <QAudioDecoder>
#include <QAudioOutput>
#include <QAudioSink>
#include <QDateTime>
#include <QMediaDevices>
#include <QUrl>
#include <qaudiobuffer.h>
#include <qaudioformat.h>

#include "../../application/appInstance.h"

bool MusicAudioSinkPlayerThread::startPlayerTread( ) {
	audioDecoder = new QAudioDecoder;
	connect( audioDecoder, &QAudioDecoder::bufferReady, [this]( ) {
		auto audioBuffer = audioDecoder->read( );
		audioBuffer.detach( );
		audioBufferVector.emplace_back( audioBuffer );
	} );
	connect( audioDecoder, &QAudioDecoder::finished, [this]( ) {
		audioDecoder->deleteLater( );
		MusicPlayerThread::startPlayerTread( );
	} );
	QUrl musicFile = QUrl::fromLocalFile( MusicPlayerThread::musicFilePath );
	audioDecoder->setSource( musicFile );
	audioDecoder->start( );

	return true;
}

MusicAudioSinkPlayerThread::MusicAudioSinkPlayerThread( const QString &load_music_file ) : MusicPlayerThread( load_music_file ) {
}

MusicAudioSinkPlayerThread::~MusicAudioSinkPlayerThread( ) {
	if( audioSink )
		audioSink->deleteLater( );
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

	ioAudioSinkDevice->write( audioBuffer.data< char >( ), audioBuffer.byteCount( ) );
	auto currentThread = QThread::currentThread( );
	size_t index;
	qint64 playerDurationMillisecond = 0;
	for( index = 1; index < count; index += 1 ) {
		// 微妙
		qint64 durationMicroseconds = audioBuffer.duration( );
		// 毫秒
		qint64 durationMillisecond = durationMicroseconds / 1000;
		playerDurationMillisecond += durationMillisecond;
		emit durationChanged( playerDurationMillisecond );
		emit positionChanged( index );
		currentThread->usleep( durationMicroseconds );
		if( isJump )
			break;
		audioBuffer = audioBufferData[ index ];
		ioAudioSinkDevice->write( audioBuffer.data< char >( ), audioBuffer.byteCount( ) );
	}
	audioSink->stop( );
	return true;
}
