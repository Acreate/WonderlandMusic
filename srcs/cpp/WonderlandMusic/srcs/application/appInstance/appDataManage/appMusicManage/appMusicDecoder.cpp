#include "appMusicDecoder.h"

#include <QFileInfo>
#include <QMetaEnum>
#include <QString>
#include <QMediaFormat>

#include <tools/stringTools.h>
#include <tools/vectorTools.h>

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
	*newItemSuffixes = newItemSuffixes->toUpper( );

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
	// 自定义添加
	appendAnyDecodeFileSuffix( "wav", "wma", "flac", "m4a", "aac", "ogg" );
	// 遍历所有支持的媒体格式
	QMediaFormat mediaFormat;
	const auto &formats = mediaFormat.supportedAudioCodecs( QMediaFormat::Decode );
	QMetaEnum metaEnum = QMetaEnum::fromType< QMediaFormat::AudioCodec >( );

	for( const auto &fmt : formats ) {
		QString *string;
		string = new QString( metaEnum.valueToKey( ( quint64 ) fmt ) );
		*string = string->toUpper( );
		supperDecodeFileSuffix.emplace_back( string );

		string = new QString( mediaFormat.audioCodecName( fmt ) );
		*string = string->toUpper( );
		supperDecodeFileSuffix.emplace_back( string );
	}
	decltype(supperDecodeFileSuffix) singleCase;
	decltype(supperDecodeFileSuffix) repetition;

	using unityType = QString *;
	VectorTools::compIdenticalTypeFinction< unityType > compFunction = [] ( auto &left_string_ptr, auto &right_string_ptr ) {
		if( *left_string_ptr == *right_string_ptr )
			return true;
		return false;
	};
	VectorTools::getRepetition( singleCase, repetition, supperDecodeFileSuffix, compFunction );
	supperDecodeFileSuffix = singleCase;
	VectorTools::deleteVectorPtr( repetition );

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
