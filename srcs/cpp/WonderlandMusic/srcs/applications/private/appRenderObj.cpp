#include "appRenderObj.h"

#include <QPainter>
#include <qfontmetrics.h>
#include <qtypes.h>

bool AppRenderObj::renderTextImage( QImage &result_image, const QString &text ) {
	return renderTextImage( result_image, text, font, color );
}
bool AppRenderObj::renderTextImage( QImage &result_image, const QString &text, const QColor &draw_color ) {
	return renderTextImage( result_image, text, font, draw_color );
}
bool AppRenderObj::renderTextImage( QImage &result_image, const QString &text, const QFont &draw_font ) {
	return renderTextImage( result_image, text, draw_font, color );
}
bool AppRenderObj::renderTextImage( QImage &result_image, const QString &text, const QFont &draw_font, const QColor &draw_color ) {
	qsizetype length = text.length( );
	if( length == 0 )
		return true;

	QFontMetrics fontMetrics( draw_font );
	int ascent = fontMetrics.ascent( );
	int height = fontMetrics.height( );
	int horizontalAdvance = fontMetrics.horizontalAdvance( text );
	QImage image( horizontalAdvance, height, QImage::Format_RGBA8888 );
	if( image.isNull( ) )
		return false;
	image.fill( 0 );
	QPainter painter;
	painter.begin( &image );
	painter.drawImage( 0, 0, result_image );
	painter.setFont( draw_font );
	QPen pen = painter.pen( );
	pen.setColor( draw_color );
	painter.setPen( pen );
	painter.drawText( 0, ascent, text );
	painter.end( );

	// 刷新
	result_image = image;
	return true;
}
bool AppRenderObj::renderOverlapImage( QImage &result_image, const QImage &top_image ) {
	int resultWidth = result_image.width( );
	int resultHeight = result_image.height( );
	int topWidth = top_image.width( );
	int topHeight = top_image.height( );

	int maxWidth = resultWidth > topWidth ? resultWidth : topWidth;
	int maxHeight = resultHeight > topHeight ? resultHeight : topHeight;

	QImage buff = QImage( maxWidth, maxHeight, QImage::Format_RGBA8888 );
	if( buff.isNull( ) )
		return false;
	buff.fill( 0 );
	QPainter painter;
	painter.begin( &buff );
	painter.drawImage( 0, 0, result_image );
	painter.drawImage( 0, 0, top_image );
	painter.end( );

	// 刷新
	result_image = buff;
	return true;
}
bool AppRenderObj::renderExpandImage( QImage &result_image, const QImage &expand_image, const QPoint &pos ) {
	int resultWidth = result_image.width( );
	int resultHeight = result_image.height( );
	int topWidth = expand_image.width( ) + pos.x( );
	int topHeight = expand_image.height( ) + pos.y( );

	int maxWidth = resultWidth > topWidth ? resultWidth : topWidth;
	int maxHeight = resultHeight > topHeight ? resultHeight : topHeight;

	QImage buff = QImage( maxWidth, maxHeight, QImage::Format_RGBA8888 );
	if( buff.isNull( ) )
		return false;
	buff.fill( 0 );
	QPainter painter;
	painter.begin( &buff );
	painter.drawImage( 0, 0, result_image );
	painter.drawImage( pos, expand_image );
	painter.end( );

	// 刷新
	result_image = buff;
	return true;
}
bool AppRenderObj::renderColorImage( QImage &result_image, const QColor &color ) {
	if( result_image.isNull( ) )
		return false;
	int resultWidth = result_image.width( );
	int resultHeight = result_image.height( );
	QImage buff = QImage( resultWidth, resultHeight, QImage::Format_RGBA8888 );
	if( buff.isNull( ) )
		return false;
	result_image.fill( color );
	result_image = buff;
	return true;
}
bool AppRenderObj::renderColorReplaceColorImage( QImage &result_image, const QColor &old_color, const QColor &new_color ) {
	if( result_image.isNull( ) )
		return false;
	int resultWidth = result_image.width( );
	int resultHeight = result_image.height( );
	QImage buff = QImage( resultWidth, resultHeight, QImage::Format_RGBA8888 );
	if( buff.isNull( ) )
		return false;
	buff.fill( 0 );
	QPainter painter;
	painter.begin( &buff );
	painter.drawImage( 0, 0, result_image );
	painter.end( );

	// 旧的透明
	int oldAlpha = old_color.alpha( );
	// 旧的红
	int oldRed = old_color.red( );
	// 旧的绿
	int oldGreen = old_color.green( );
	// 旧的蓝
	int oldBlue = old_color.blue( );

	// 新的透明
	int newAlpha = new_color.alpha( );
	// 新的红
	int newRed = new_color.red( );
	// 新的绿
	int newGreen = new_color.green( );
	// 新的蓝
	int newBlue = new_color.blue( );

	// 首地址
	uchar *pData = buff.bits( );
	int bytesPerLine = buff.bytesPerLine( );
	int imageWidth = buff.width( );
	int imageHeight = buff.height( );
	int bitY;
	int bitX;
	// pLine[0]=B
	int blueOffset;
	// pLine[1]=G
	int greenOffset;
	// pLine[2]=R
	int redOffset;
	// pLine[3]=A
	int alphaOffset;
	int offset;
	uchar *pLine;
	for( bitY = 0; bitY < imageHeight; bitY++ )
		for( bitX = 0, pLine = pData + bitY * bytesPerLine; bitX < imageWidth; bitX++ ) {
			offset = bitX * 4;
			blueOffset = offset + 0;
			greenOffset = offset + 1;
			redOffset = offset + 2;
			alphaOffset = offset + 3;
			if( pLine[ blueOffset ] == oldBlue && pLine[ greenOffset ] == oldGreen && pLine[ redOffset ] == oldRed && pLine[ alphaOffset ] == oldAlpha ) {
				pLine[ blueOffset ] = newBlue;
				pLine[ greenOffset ] = newGreen;
				pLine[ redOffset ] = newRed;
				pLine[ alphaOffset ] = newAlpha;
			}
		}
	result_image = buff;
	return true;
}
