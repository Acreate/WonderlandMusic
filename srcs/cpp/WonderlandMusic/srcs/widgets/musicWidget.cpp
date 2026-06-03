#include "musicWidget.h"
#include <QDir>
#include <QMediaFormat>
#include <QMetaEnum>
#include <QFileInfo>
MusicWidget::MusicWidget( QWidget *parent, const Qt::WindowFlags &f ) : QWidget( parent, f ) {
	dirPtr = new QDir;

	fileInfo = new QFileInfo;
	QMediaFormat mediaFormat;
	auto audioCodecs = mediaFormat.supportedAudioCodecs( QMediaFormat::Decode );
	qsizetype count = audioCodecs.size( );
	if( count == 0 )
		return;
	QMediaFormat::AudioCodec *audioCodec = audioCodecs.data( );
	qsizetype index = 0;
	supportedAudioCodecs.resize( count );
	auto data = supportedAudioCodecs.data( );
	auto metaEnum = QMetaEnum::fromType< QMediaFormat::AudioCodec >( );
	for( ; index < count; ++index )
		data[ index ] = metaEnum.valueToKey( ( quint64 ) ( audioCodec[ index ] ) ), data[ index ] = data[ index ].toUpper( );

}
MusicWidget::~MusicWidget( ) {
	delete dirPtr;
	delete fileInfo;
}
void MusicWidget::loadPathMusicFile( const std::vector< QString > &path ) {
	std::vector< Music * > result;
	size_t count = path.size( );
	if( count == 0 )
		return;
	auto data = path.data( );
	size_t index = 0;
	for( ; index < count; ++index )
		loadPathMusicFile( data[ index ] );
}
void MusicWidget::loadPathMusicFile( const QString &path ) {
	if( dirPtr->exists( path ) == false )
		return;
	fileInfo->setFile( path );
	if( fileInfo->isFile( ) ) {
		if( isSupportedAudioCodecs( fileInfo->absoluteFilePath( ) ) == false )
			return;
	} else {
		dirPtr->setCurrent( path );
		auto entryInfoList = dirPtr->entryInfoList( QDir::NoDotAndDotDot );
		qsizetype count = entryInfoList.size( );
		if( count == 0 )
			return;
		auto fileInfoArray = entryInfoList.data( );
		qsizetype index = 0;
		for( ; index < count; ++index )
			loadPathMusicFile( fileInfoArray[ index ].absoluteFilePath( ) );
	}
}
bool MusicWidget::isSupportedAudioCodecs( const QString &file_name ) const {
	qsizetype lastIndexOf = file_name.lastIndexOf( "." );
	if( lastIndexOf == -1 )
		return false;
	auto count = supportedAudioCodecs.size( );
	if( count == 0 )
		return false;
	auto data = supportedAudioCodecs.data( );
	size_t index = 0;
	// 获取 .后的字符串
	auto suffix = file_name.mid( lastIndexOf + 1 ).toUpper( );
	for( ; index < count; ++index )
		if( data[ index ] == suffix )
			return true;
	return false;
}
