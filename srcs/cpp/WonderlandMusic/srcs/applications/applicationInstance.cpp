#include "applicationInstance.h"

#include <QFontDatabase>
#include <QFont>
#include <QPainter>
#include <qcolor.h>
#include <qfontmetrics.h>
#include <qimage.h>

#include "../render/render.h"

class AppRenderObj : public Render {
	friend class ApplicationInstance;
private:
	QFont font;
	QColor color;
private:
	AppRenderObj( const QFont &font, const QColor &color )
		: font( font ),
		color( color ) { }
protected:
	~AppRenderObj( ) override { }
public:
	bool render( QImage &result_image, const QString &text ) override;
	bool renderOverlapImage( QImage &result_image, const QImage &top_image ) override;
	bool renderExpandImage( QImage &result_image, const QImage &expand_image, const QPoint &pos ) override;
	bool renderColorImage( QImage &result_image, const QColor &color ) override;
	bool renderColorReplaceColorImage( QImage &result_image, const QColor &old_color, const QColor &new_color ) override;
};

bool AppRenderObj::render( QImage &result_image, const QString &text ) {
	qsizetype length = text.length( );
	if( length == 0 )
		return true;

	QFontMetrics fontMetrics( font );
	int ascent = fontMetrics.ascent( );
	int height = fontMetrics.height( );
	int horizontalAdvance = fontMetrics.horizontalAdvance( text );
	QImage image( horizontalAdvance, height, QImage::Format_RGBA8888 );
	if( image.isNull( ) )
		return false;
	image.fill( 0 );
	QPainter painter;
	painter.begin( &image );
	painter.setFont( font );
	QPen pen = painter.pen( );
	pen.setColor( color );
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
	result_image.fill( color );
	return true;
}
bool AppRenderObj::renderColorReplaceColorImage( QImage &result_image, const QColor &old_color, const QColor &new_color ) {
	if( result_image.isNull( ) )
		return false;
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
	uchar *pData = result_image.bits( );
	int bytesPerLine = result_image.bytesPerLine( );
	int imageWidth = result_image.width( );
	int imageHeight = result_image.height( );
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
	uchar *pLine;
	for( bitY = 0; bitY < imageHeight; bitY++ )
		for( bitX = 0, pLine = pData + bitY * bytesPerLine; bitX < imageWidth; bitX++ ) {
			blueOffset = bitX * 4 + 0;
			greenOffset = bitX * 4 + 1;
			redOffset = bitX * 4 + 2;
			alphaOffset = bitX * 4 + 3;
			if( pLine[ blueOffset ] == oldBlue && pLine[ greenOffset ] == oldGreen && pLine[ redOffset ] == oldRed && pLine[ alphaOffset ] == oldAlpha ) {
				pLine[ blueOffset ] = newBlue;
				pLine[ greenOffset ] = newGreen;
				pLine[ redOffset ] = newRed;
				pLine[ alphaOffset ] = newAlpha;
			}
		}
	return true;
}
ApplicationInstance *ApplicationInstance::instance = nullptr;
ApplicationInstance::ApplicationInstance( Application *const application ) : application( application ) {
	QFont customFont = QFont( "Microsoft YaHei", 14 ); // 使用外部字体
	// 加载字体
	int fontId = QFontDatabase::addApplicationFont( ":/font/Alibaba/Alibaba-PuHuiTi-Medium.ttf" );

	QStringList familyList;
	if( fontId != -1 ) {
		familyList = QFontDatabase::applicationFontFamilies( fontId );
		if( !familyList.isEmpty( ) ) {
			QString familyName = familyList.first( );
			customFont = QFont( familyName, 14 );
		}
	}
	render = new AppRenderObj( customFont, Qt::GlobalColor::black );
}
ApplicationInstance::~ApplicationInstance( ) {
	delete render;
}
ApplicationInstance * ApplicationInstance::getInstance( ) {
	return instance;
}
