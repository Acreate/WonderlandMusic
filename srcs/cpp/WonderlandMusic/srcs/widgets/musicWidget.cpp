#include "musicWidget.h"
#include <QDir>
#include <QUrl>
#include <QMediaFormat>
#include <QAudioDecoder>
#include <QMetaEnum>
#include <QFileInfo>
#include "../musics/music.h"
#include "../msgInfo/messageErrorOut.h"

#include "subWidget/appFunctionWidget.h"
#include "subWidget/musicPlayerButtonWidget.h"
#include "subWidget/musicPlayerWidget.h"
#include "subWidget/musicVectorInfoWidget.h"

MusicWidget::MusicWidget( QWidget *parent, const Qt::WindowFlags &f ) : QWidget( parent, f ) {
	dirPtr = new QDir;
	fileInfo = new QFileInfo;
	appFunctionWidget = new AppFunctionWidget( this );
	musicPlayerWidget = new MusicPlayerWidget( this );
	musicVectorInfoWidget = new MusicVectorInfoWidget( this );
	musicPlayerButtonWidget = new MusicPlayerButtonWidget( this );
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
void MusicWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
	// 当前面板矩阵
	auto currentMainWidgetContentsRect = contentsRect( );
	// 当前主要窗口高度
	int currentMainWidgetHieght = currentMainWidgetContentsRect.height( ) - currentMainWidgetContentsRect.y( );
	// 当前主要窗口宽度
	int currentMainWidgetWidth = currentMainWidgetContentsRect.width( ) - currentMainWidgetContentsRect.x( );

	// 面板起始的位置
	int widgetStartX = 0;
	// 播放功能高度
	int musicPlayerButtonWidgetHeight = musicPlayerButtonWidget->height( );
	// 剩余高度
	int modHeight = currentMainWidgetHieght - musicPlayerButtonWidgetHeight;
	// 配置播放功能面板
	musicPlayerButtonWidget->setGeometry( widgetStartX, modHeight, currentMainWidgetWidth, musicPlayerButtonWidgetHeight );

	// 配置功能面板位置与大小
	int appFunctionWidgetWidth = appFunctionWidget->width( );
	appFunctionWidget->setGeometry( widgetStartX, 0, appFunctionWidgetWidth, modHeight );

	// 下一个面板
	widgetStartX = appFunctionWidgetWidth + widgetStartX;
	// 配置播放面板
	int musicPlayerWidgetWidth = musicPlayerWidget->width( );
	musicPlayerWidget->setGeometry( widgetStartX, 0, musicPlayerWidgetWidth, modHeight );

	// 下一个面板
	widgetStartX = musicPlayerWidgetWidth + widgetStartX;
	// 剩余宽度
	int modWidth = currentMainWidgetWidth - widgetStartX;
	// 配置音乐列表信息面板
	musicVectorInfoWidget->setGeometry( widgetStartX, 0, modWidth, modHeight );

	#undef get_offset_start
}
