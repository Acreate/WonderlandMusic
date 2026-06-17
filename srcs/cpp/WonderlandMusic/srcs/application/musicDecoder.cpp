#include "musicDecoder.h"

#include <QMetaEnum>
#include <QString>
#include <QMediaFormat>

MusicDecoder::~MusicDecoder( ) {
	size_t count = supperDecodeFileSuffix.size( );
	if( count ) {
		auto data = supperDecodeFileSuffix.data( );
		size_t index = 0;
		for( ; index < count; index += 1 )
			delete data[ index ];
		supperDecodeFileSuffix.clear( );
	}

}
MusicDecoder::MusicDecoder( ) { }
bool MusicDecoder::musicFileNmaeSupperDecoder( const QString &music_file_path ) const {
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
bool MusicDecoder::init( ) {
	// 遍历所有支持的媒体格式
	QMediaFormat mediaFormat;
	const auto &formats = mediaFormat.supportedAudioCodecs( QMediaFormat::Decode );
	QMetaEnum metaEnum = QMetaEnum::fromType< QMediaFormat::AudioCodec >( );
	for( const auto &fmt : formats ) {
		QString *string = new QString( metaEnum.valueToKey( ( quint64 ) fmt ) );
		*string = string->toUpper( );
		supperDecodeFileSuffix.emplace_back( string );
	}
	return true;
}
std::vector< QString > MusicDecoder::getSupperDecodeFileSuffix( ) const {
	size_t count = supperDecodeFileSuffix.size( );
	std::vector< QString > result( count );
	auto data = supperDecodeFileSuffix.data( );
	auto resultData = result.data( );
	size_t index = 0;
	for( ; index < count; index += 1 )
		resultData[ index ] = *data[ index ];

	return result;
}
