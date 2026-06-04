#include "musicWidget.h"
#include <QDir>
#include <QMediaFormat>
#include <QMetaEnum>
#include <QFileInfo>

#include "../musics/music.h"

#include "../applications/applicationInstance.h"

#include "../msgInfo/messageErrorOut.h"

#include "../render/render.h"

#include <QLabel>
#include <QVBoxLayout>

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

	auto applicationInstance = ApplicationInstance::getInstance( );

	QImage buff;
	if( applicationInstance->getRender( )->render( buff, tr( "L I l i k g 一起 打怪罪" ) ) == false )
		MessageErrorOut( ) << tr( "加载失败" );
	else
		buff.save( "log/buff.png" );
	QLabel *showRender = new QLabel( this );
	showRender->setPixmap( QPixmap::fromImage( buff ) );
	QVBoxLayout *mainLayout = new QVBoxLayout( this );
	mainLayout->addWidget( showRender, 0, Qt::AlignTop | Qt::AlignmentFlag::AlignLeft );
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
