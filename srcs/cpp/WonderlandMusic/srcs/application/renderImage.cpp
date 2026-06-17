#include "renderImage.h"

#include <QFontDatabase>
#include <QPainter>
#include <QWidget>
RenderImage::RenderImage( ) {
	brackGroundColor = new QColor( 0, 0, 0, 0 );
	drawPenColor = new QColor( 0, 0, 0, 255 );
	drawPen = new QPen;
	drawPen->setColor( *drawPenColor );
	font = new QFont( "Microsoft YaHei", 14 );
	fontMetrics = new QFontMetrics( *font );
	fontMetricsHeight = fontMetrics->height( );

	fontMetricsAscent = fontMetrics->ascent( );;
}
RenderImage::~RenderImage( ) {
	delete fontMetrics;
	delete font;
	delete brackGroundColor;
	delete drawPenColor;
	delete drawPen;
}
bool RenderImage::init( ) {
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
	fontMetricsHeight = fontMetrics->height( );
	fontMetricsAscent = fontMetrics->ascent( );;
	return true;
}
const QFont * RenderImage::getFont( ) const { return font; }
const QFontMetrics * RenderImage::getFontMetrics( ) const { return fontMetrics; }
bool RenderImage::renderTxt( QImage &result_render_image, const QString &render_txt ) const {
	int renderWidth = fontMetrics->horizontalAdvance( render_txt );
	auto buffImage = QImage( renderWidth, fontMetricsHeight, QImage::Format_RGBA8888 );
	if( buffImage.isNull( ) )
		return false;
	QPainter painter;
	painter.begin( &buffImage );
	painter.fillRect( 0, 0, renderWidth, fontMetricsHeight, *brackGroundColor );
	painter.setPen( *drawPen );
	painter.setFont( *font );
	painter.drawText( 0, fontMetricsAscent, render_txt );
	painter.end( );
	result_render_image = buffImage;
	return true;
}
bool RenderImage::renderWidget( QImage &result_render_image, QWidget *render_widget ) const {

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
