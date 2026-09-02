#include "appMusicDecoder.h"

#include <QFileInfo>
#include <QString>

#include <tools/stringTools.h>
#include <tools/vectorTools.h>

#include <head/extern_c.h>

INCLUDE_EXTERN_C {
	#include <libavformat/avformat.h>
}

AppMusicDecoder::~AppMusicDecoder( ) {
	deleteResource( );
}

AppMusicDecoder::AppMusicDecoder( ) {
}

bool AppMusicDecoder::musicFileNmaeSupperDecoder( const QString &music_file_path ) const {
	size_t count = supperDecodeFileSuffix.size( );
	if( count == 0 )
		return false; // 没有正确解析后缀
	qsizetype indexOf = music_file_path.indexOf( "." );
	if( indexOf == -1 )
		return false; // 没有后缀
	auto compString = music_file_path.mid( indexOf + 1 );
	compString = compString.toUpper( );
	auto data = supperDecodeFileSuffix.data( );
	size_t index = 0;
	for( ; index < count; index += 1 )
		if( *data[ index ] == compString )
			return true;
	return false;
}

AppMusicDecoder::StringOperator::StringOperator( ) {
	this->stringList = new QStringList;
}

AppMusicDecoder::StringOperator::~StringOperator( ) {
	delete stringList;
}

AppMusicDecoder::StringOperator & AppMusicDecoder::StringOperator::operator<<( const QString &append ) {
	*stringList << append;
	return *this;
}

void AppMusicDecoder::appendDecodeFileSuffix( const QString &decode_file_suffix ) {
	QString *newItemSuffixes = new QString( StringTools::getFileSuffix( decode_file_suffix ).toUpper( ) );
	supperDecodeFileSuffix.emplace_back( newItemSuffixes );
}

void AppMusicDecoder::appendDecodeFileSuffix( const QStringList &decode_file_suffix ) {
	auto count = decode_file_suffix.size( );
	if( count == 0 )
		return;
	auto data = decode_file_suffix.data( );
	decltype(count) index = 0;
	for( ; index < count; index += 1 )
		appendDecodeFileSuffix( data[ index ] );
}
bool AppMusicDecoder::init( ) {
	void *opaque = nullptr;
	const AVOutputFormat *ofmt;
	QString buff;
	QStringList spliteStringList;
	qsizetype count;
	qsizetype index;
	QString *data;
	while( ( ofmt = av_muxer_iterate( &opaque ) ) != nullptr ) {
		if( ofmt->audio_codec == AV_CODEC_ID_NONE )
			continue;
		if( ofmt->extensions == nullptr || ofmt->extensions[ 0 ] == '\0' )
			continue;
		buff = QString::fromUtf8( ofmt->extensions );
		spliteStringList = buff.split( "," );
		count = spliteStringList.size( );
		data = spliteStringList.data( );
		for( index = 0; index < count; index += 1 )
			appendDecodeFileSuffix( data[ index ] );
	}
	return true;
}

bool AppMusicDecoder::initBefore( ) {
	deleteResource( );
	return true;
}

bool AppMusicDecoder::initAfter( ) {
	return true;
}

bool AppMusicDecoder::deleteResource( ) {
	VectorTools::deleteVectorPtr( supperDecodeFileSuffix );
	supperDecodeFileSuffix.clear( );
	return true;
}

std::vector< QString > AppMusicDecoder::getSupperDecodeFileSuffix( ) const {
	size_t count = supperDecodeFileSuffix.size( );
	std::vector< QString > result( count );
	auto data = supperDecodeFileSuffix.data( );
	auto resultData = result.data( );
	size_t index = 0;
	for( ; index < count; index += 1 )
		resultData[ index ] = *data[ index ];

	return result;
}
