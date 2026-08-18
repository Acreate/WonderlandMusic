#include "appRenderImage.h"

#include <QFontDatabase>
#include <QPainter>
#include <QWidget>

#include <head/release_macro.h>

#include "../../../../component/musicWindow/interface/info/iMusicItemWidthInfo.h"
#include "../../../../component/musicWindow/interface/item/iMusicItem.h"

#include "../../../../head/result_message_out.h"

#include "../../../../tools/instanceTools.h"

bool AppRenderImage::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( brackGroundColor );
	Delete_Resource_App_Core_Ptr( drawPenColor );
	Delete_Resource_App_Core_Ptr( drawPen );
	Delete_Resource_App_Core_Ptr( font );
	Delete_Resource_App_Core_Ptr( fontMetrics );
	return true;
}

AppRenderImage::AppRenderImage( ) {
}

AppRenderImage::~AppRenderImage( ) {
}

bool AppRenderImage::initBefore( ) {
	return true;
}

bool AppRenderImage::initAfter( ) {
	return true;
}

bool AppRenderImage::init( ) {
	brackGroundColor = new QColor( 0, 0, 0, 0 );
	drawPenColor = new QColor( 0, 0, 0, 255 );
	drawPen = new QPen( *drawPenColor );
	font = new QFont( "Microsoft YaHei", 14 );
	fontMetrics = new QFontMetrics( *font );

	auto ttfFilePath = "./program/font/Alibaba/Alibaba-PuHuiTi-Medium.ttf";
	// 使用外部字体，加载字体
	int fontId = QFontDatabase::addApplicationFont( ttfFilePath );

	if( fontId == -1 )
		return Result_Var_Messag_Ptr_Out_Args( false, nullptr, QFontDatabase::addApplicationFont, QObject:: tr("配置文字路径异常: %1").arg( ttfFilePath ) );

	QStringList familyList = QFontDatabase::applicationFontFamilies( fontId );
	if( familyList.isEmpty( ) )
		return Result_Var_Messag_Ptr_Out_Args( false, nullptr, QFontDatabase::applicationFontFamilies, QObject:: tr("配置文字异常: %1").arg( fontId ) );

	QString familyName = familyList.first( );
	*font = QFont( familyName, 14 );
	*fontMetrics = QFontMetrics( *font );
	return true;
}

const QFont * AppRenderImage::getFont( ) const {
	return font;
}

const QFontMetrics * AppRenderImage::getFontMetrics( ) const {
	return fontMetrics;
}

bool AppRenderImage::renderTxt( QImage &result_render_image, const QString &render_txt, const QFont &font, const QFontMetrics &font_metrics ) const {
	int renderWidth = font_metrics.horizontalAdvance( render_txt );
	auto buffImage = QImage( renderWidth, fontMetrics->height( ), QImage::Format_RGBA8888 );
	if( buffImage.isNull( ) )
		return false;
	buffImage.fill( 0 );
	QPainter painter;
	painter.begin( &buffImage );
	painter.fillRect( 0, 0, renderWidth, fontMetrics->height( ), *brackGroundColor );
	painter.setPen( *drawPen );
	painter.setFont( font );
	painter.drawText( 0, fontMetrics->ascent( ), render_txt );
	painter.end( );
	result_render_image = buffImage;
	return true;
}
bool AppRenderImage::getTxtSize( QSize &result_txt_size, const QString &render_txt, const QFontMetrics &font_metrics ) const {
	if( render_txt.isEmpty( ) )
		return false;
	result_txt_size = QSize( font_metrics.horizontalAdvance( render_txt ), fontMetrics->height( ) );
	return true;
}
bool AppRenderImage::renderTxt( QImage &result_render_image, const QString &render_txt ) const {
	return renderTxt( result_render_image, render_txt, *font, *fontMetrics );
}
bool AppRenderImage::renderTxt( QImage &result_render_image, const QString &render_txt, const QFont &font ) const {
	if( &font == this->font || font == *this->font )
		return renderTxt( result_render_image, render_txt, *this->font, *this->fontMetrics );
	return renderTxt( result_render_image, render_txt, font, QFontMetrics( font ) );
}
bool AppRenderImage::getTxtSize( QSize &result_txt_size, const QString &render_txt, const QFont &font ) const {
	return getTxtSize( result_txt_size, render_txt, QFontMetrics( font ) );
}
bool AppRenderImage::getTxtSize( QSize &result_txt_size, const QString &render_txt ) const {
	return getTxtSize( result_txt_size, render_txt, *this->fontMetrics );
}

bool AppRenderImage::renderWidget( QImage &result_render_image, QWidget *render_widget ) const {
	if( render_widget == nullptr )
		return false;

	render_widget->adjustSize( );
	QSize size = render_widget->size( );
	QImage buff = QImage( size, QImage::Format_RGBA8888 );
	if( buff.isNull( ) )
		return false;
	QPainter painter;
	painter.begin( &buff );
	int width = size.width( );
	int height = size.height( );
	painter.fillRect( 0, 0, width, height, *brackGroundColor );
	render_widget->render( &painter );
	painter.end( );

	return true;
}
bool AppRenderImage::renderMusicItem( QImage &result_render_image, IMusicItem *music_item, const IMusicItemWidthInfo *item_width_info ) const {
	size_t idCode;
	if( music_item->getIdCode( idCode ) == false )
		return Result_Var_Messag_Ptr_Out_Args( false, music_item, getIdCode, QObject::tr( "获取歌曲id失败" ) );
	QString name;
	if( music_item->getName( name ) == false )
		return Result_Var_Messag_Ptr_Out_Args( false, music_item, getName, QObject::tr( "获取歌曲名称失败" ) );
	QString singer;
	if( music_item->getSinger( singer ) == false )
		return Result_Var_Messag_Ptr_Out_Args( false, music_item, getSinger, QObject::tr( "获取歌曲歌手失败" ) );
	QString elapsedTimeString;
	if( music_item->getElapsedTimeString( elapsedTimeString ) == false )
		return Result_Var_Messag_Ptr_Out_Args( false, music_item, getElapsedTimeString, QObject::tr( "获取时间字符串失败" ) );
	int calculateMinWidth = item_width_info->getCalculateMinWidth( );
	int calculateMinHeight = fontMetrics->height( );
	QImage buff( calculateMinWidth, calculateMinHeight, QImage::Format_RGBA8888 );
	if( buff.isNull( ) )
		return Result_Var_Messag_Ptr_Out_Args( false, &buff, isNull, QObject::tr( "创建绘制缓存失败" ) );
	buff.fill( 0 );
	QPainter painter;
	painter.begin( &buff );
	painter.setFont( *font );
	int separatorWidth = item_width_info->getSeparatorWidth( );
	int intervalWidth = item_width_info->getIntervalWidth( );
	QColor fillSeparatorColor( 255, 255, 255, 255 );
	painter.fillRect( QRect( intervalWidth, 0, separatorWidth, calculateMinHeight ), fillSeparatorColor );

	intervalWidth += intervalWidth + separatorWidth;

	QString text = QString::number( idCode );
	int musicCodeWidth = item_width_info->getMusicCodeWidth( );
	painter.drawText( QRect( intervalWidth, 0, musicCodeWidth, calculateMinHeight ), text );

	intervalWidth += intervalWidth + musicCodeWidth;
	painter.fillRect( QRect( intervalWidth, 0, separatorWidth, calculateMinHeight ), fillSeparatorColor );

	intervalWidth += intervalWidth + separatorWidth;
	painter.drawText( QRect( intervalWidth, 0, musicCodeWidth, calculateMinHeight ), name );

	int musicNameWidth = item_width_info->getMusicNameWidth( );
	intervalWidth += intervalWidth + musicNameWidth;
	painter.fillRect( QRect( intervalWidth, 0, separatorWidth, calculateMinHeight ), fillSeparatorColor );

	intervalWidth += intervalWidth + separatorWidth;
	painter.drawText( QRect( intervalWidth, 0, musicCodeWidth, calculateMinHeight ), singer );

	int musicSingerNameWidth = item_width_info->getMusicSingerNameWidth( );
	intervalWidth += intervalWidth + musicSingerNameWidth;
	painter.fillRect( QRect( intervalWidth, 0, separatorWidth, calculateMinHeight ), fillSeparatorColor );

	intervalWidth += intervalWidth + separatorWidth;
	painter.drawText( QRect( intervalWidth, 0, musicCodeWidth, calculateMinHeight ), elapsedTimeString );

	int musicDurationTimeWidth = item_width_info->getMusicDurationTimeWidth( );
	intervalWidth += intervalWidth + musicDurationTimeWidth;
	painter.fillRect( QRect( intervalWidth, 0, separatorWidth, calculateMinHeight ), fillSeparatorColor );

	painter.end( );
	if( music_item->setDrawBuff( buff ) == false )
		return Result_Var_Messag_Ptr_Out_Args( false, music_item, setDrawBuff, QObject::tr( "配置绘制缓存失败" ) );
	return true;
}
bool AppRenderImage::renderMusicItem( QImage &result_render_image, IMusicFavoriteItem *music_favorite_item, const IMusicItemWidthInfo *item_width_info ) const {
	return false;
}
