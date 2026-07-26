#include "appRenderImage.h"

#include <QFontDatabase>
#include <QPainter>
#include <QWidget>

#include "../head/release_macro.h"

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

	// 使用外部字体，加载字体
	int fontId = QFontDatabase::addApplicationFont( "./program/font/Alibaba/Alibaba-PuHuiTi-Medium.ttf" );

	if( fontId == 1 )
		return false;

	QStringList familyList = QFontDatabase::applicationFontFamilies( fontId );
	if( familyList.isEmpty( ) )
		return false;

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
