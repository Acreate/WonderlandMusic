#include "musicDecode.h"

#include <QAudioDecoder>
#include <QFileInfo>
#include <QUrl>

#include "../msgInfo/messageErrorOut.h"

void MusicDecode::deleteResource( ) {
	#define d_r( ptr ) if(ptr) (delete ptr, ptr = nullptr)
	d_r( audioDecoder );
	d_r( loadUrl );
}

MusicDecode::~MusicDecode( ) {
	deleteResource( );
}

MusicDecode::MusicDecode( ) {
}

bool MusicDecode::init( ) {
	deleteResource( );
	loadUrl = new QUrl;
	audioDecoder = new QAudioDecoder;

	connect( audioDecoder, &QAudioDecoder::bufferReady, [this]( ) {
		QAudioBuffer audioBuffer = audioDecoder->read( );
		audioBuffer.detach( );
		audioBufferVector.emplace_back( audioBuffer );
	} );
	connect( audioDecoder, &QAudioDecoder::finished, [this]( ) {
		emit finished_Signal( audioBufferVector );
	} );
	auto audioDecoderErrorSignal = qOverload< QAudioDecoder::Error >( &QAudioDecoder::error );
	connect( audioDecoder, audioDecoderErrorSignal, [this] ( QAudioDecoder::Error error ) {
		emit error_Signal( ( Error ) error, audioDecoder->errorString( ) );
	} );

	return true;
}

bool MusicDecode::setSource( const QUrl &url ) {
	*loadUrl = url;
	if( audioDecoder->isDecoding( ) )
		audioDecoder->stop( );
	audioBufferVector.clear( );
	audioDecoder->setSource( url );
	return true;
}

bool MusicDecode::setSource( const QString &file_path ) {
	return setSource( QUrl::fromLocalFile( QFileInfo( file_path ).absoluteFilePath( ) ) );
}

bool MusicDecode::start( ) {
	audioBufferVector.clear( );
	audioDecoder->start( );
	return true;
}

bool MusicDecode::stop( ) {
	if( audioDecoder->isDecoding( ) == false )
		return false;
	audioDecoder->stop( );
	return true;
}

bool MusicDecode::isDecoding( ) {
	return audioDecoder->isDecoding( );
}

const QUrl * MusicDecode::getLoadUrl( ) const {
	return loadUrl;
}
