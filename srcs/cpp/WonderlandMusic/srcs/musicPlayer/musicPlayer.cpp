#include "musicPlayer.h"

#include <QAudioSink>
#include <QMediaPlayer>
#include <QIODevice>
#include <QAudioOutput>
#include <QAudioDevice>
#include <QMediaDevices>
#include <QFileInfo>
#include <QAudioDecoder>

#include "../application/appInstance.h"

#include "../msgInfo/messageErrorOut.h"

#include "../tools/autoMakePtrTools.h"

#define  d_r( ptr ) if(ptr) (delete ptr, ptr = nullptr)

void MusicPlayer::deleteResource( ) {
	d_r( audioSink );
	d_r( audioDecoder );
	d_r( mediaPlayer );
}

void MusicPlayer::bufferReady( ) {
	if( audioSink == nullptr ) {
		//auto audioFormat = audioDecoder->audioFormat( );

		QAudioFormat audioFormat;

		audioFormat.setSampleRate( 44100 );
		audioFormat.setChannelCount( 1 );
		audioFormat.setSampleFormat( QAudioFormat::Int16 );

		QAudioDevice info( QMediaDevices::defaultAudioOutput( ) );
		if( !info.isFormatSupported( audioFormat ) ) {
			qWarning( ) << "Raw audio format not supported by backend, cannot play audio.";
			return;
		}
		audioSink = new QAudioSink( audioFormat );
		audioSink->setVolume( 1.0 );
		ioDevice = audioSink->start( );
	}

	QAudioBuffer audioBuffer = audioDecoder->read( );
	if( audioBuffer.isValid( ) == false || ioDevice == nullptr )
		return;
	qint64 byteCount = audioBuffer.byteCount( );
	if( byteCount == 0 )
		return;
	auto constData = audioBuffer.constData< char >( );
	ioDevice->write( constData, byteCount );
}

void MusicPlayer::finished( ) {
	auto audioFormat = audioDecoder->audioFormat( );

	d_r( audioSink );
}

void MusicPlayer::formatChanged( const QAudioFormat &fmt ) {
	QAudioDevice info( QMediaDevices::defaultAudioOutput( ) );
	if( !info.isFormatSupported( fmt ) ) {
		qWarning( ) << "Raw audio format not supported by backend, cannot play audio.";
		return;
	}
	audioSink = new QAudioSink( fmt );
	audioSink->setVolume( 1.0 );
	ioDevice = audioSink->start( );
}

MusicPlayer::MusicPlayer( QObject *parent ) : QObject( parent ) {
}

bool MusicPlayer::init( ) {
	deleteResource( );
	audioOutput = new QAudioOutput( this );
	audioOutput->setVolume( 1 );
	ioDevice = nullptr;
	audioDecoder = new QAudioDecoder;
	mediaPlayer = new QMediaPlayer;
	mediaPlayer->setAudioOutput( audioOutput );

	connect( audioDecoder, &QAudioDecoder::finished, this, &MusicPlayer::finished );
	connect( audioDecoder, &QAudioDecoder::formatChanged, this, &MusicPlayer::formatChanged,
			Qt::QueuedConnection );
	connect( audioDecoder, &QAudioDecoder::bufferReady, this, &MusicPlayer::bufferReady );
	auto overload = qOverload< QAudioDecoder::Error >( &QAudioDecoder::error );
	connect( audioDecoder, overload, [this] ( QAudioDecoder::Error error ) {
		Message_Error_Out << error + " : " << audioDecoder->errorString( );
	} );
	return true;
}

bool MusicPlayer::playerMusic( const QString &music_file ) {
	QFileInfo loadMusicFileInfo( music_file );
	if( loadMusicFileInfo.exists( ) == false )
		return false;
	if( mediaPlayer->isPlaying( ) )
		mediaPlayer->stop( );
	musicFilePath = loadMusicFileInfo.absoluteFilePath( );
	mediaPlayer->setSource( QUrl::fromLocalFile( musicFilePath ) );
	mediaPlayer->play( );
	return true;
}
