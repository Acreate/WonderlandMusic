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
	return false;
}
bool AppRenderObj::renderExpandImage( QImage &result_image, const QImage &expand_image, const QPoint &pos ) {
	return false;
}
bool AppRenderObj::renderColorImage( QImage &result_image, const QColor &color ) {
	return false;
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
