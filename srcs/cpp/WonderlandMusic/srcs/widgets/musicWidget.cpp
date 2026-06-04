#include "musicWidget.h"
#include <QDir>
#include <QUrl>
#include <QMediaFormat>
#include <QAudioDecoder>
#include <QMetaEnum>
#include <QFileInfo>
#include "../musics/music.h"
#include "../msgInfo/messageErrorOut.h"

MusicWidget::MusicWidget( QWidget *parent, const Qt::WindowFlags &f ) : QWidget( parent, f ) {
	dirPtr = new QDir;

	fileInfo = new QFileInfo;

	if( isSupportedAudioCodecs( "./program/music/20Hz-stero.wav" ) )
		MessageErrorOut( ) << "支持 wav";
	if( isSupportedAudioCodecs( "./program/music/20kHz.flac" ) )
		MessageErrorOut( ) << "支持 flac";
	if( isSupportedAudioCodecs( "./program/music/20kHz.mp3" ) )
		MessageErrorOut( ) << "支持 mp3";

}
MusicWidget::~MusicWidget( ) {

	size_t count = musicsLoadPlanVector.size( );
	if( count ) {
		size_t index = 0;
		auto data = musicsLoadPlanVector.data( );
		for( ; index < count; ++index )
			delete data[ index ];
		musicsLoadPlanVector.clear( );
	}

	delete dirPtr;
	delete fileInfo;
}
void MusicWidget::loadPathMusicFile( const std::vector< QString > &path ) {
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
	if( fileInfo->isFile( ) == false ) {
		dirPtr->setCurrent( path );
		auto entryInfoList = dirPtr->entryInfoList( QDir::NoDotAndDotDot );
		qsizetype count = entryInfoList.size( );
		if( count == 0 )
			return;
		auto fileInfoArray = entryInfoList.data( );
		qsizetype index = 0;
		for( ; index < count; ++index )
			loadPathMusicFile( fileInfoArray[ index ].absoluteFilePath( ) );
		return; // 目录完成递归检查，则返回
	}
	QString absoluteFilePath = fileInfo->absoluteFilePath( );
	if( isSupportedAudioCodecs( absoluteFilePath ) == false )
		return; // 不支持格式，则返回
	size_t count = musicsLoadPlanVector.size( );
	// 检查是否存在重复
	if( count > 0 ) {
		size_t index = 0;
		auto data = musicsLoadPlanVector.data( );
		for( ; index < count; ++index )
			if( data[ index ]->getMusicPath( ) == absoluteFilePath )
				return; // 如果已经存在，则返回
	}
	// 未重复，则加入新对象
	auto newMusic = new Music( absoluteFilePath );
	musicsLoadPlanVector.emplace_back( newMusic );
}
bool MusicWidget::isSupportedAudioCodecs( const QString &file_name ) const {
	QAudioDecoder audioDecoder;
	audioDecoder.setSource( QUrl::fromLocalFile( file_name ) );
	return audioDecoder.isSupported( );
}
