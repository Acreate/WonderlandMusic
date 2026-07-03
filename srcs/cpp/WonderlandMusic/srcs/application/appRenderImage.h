#ifndef APPRENDERIMAGE_H_H_HEAD__FILE__
#define APPRENDERIMAGE_H_H_HEAD__FILE__
#include "../interface/iAppCore.h"

class QWidget;
class QPen;
class QColor;
class QString;
class QImage;
class QFontMetrics;
class QFont;

class AppRenderImage : public IAppCore {
protected:
	QFont *font = nullptr;
	QFontMetrics *fontMetrics = nullptr;
	QColor *brackGroundColor = nullptr;
	QColor *drawPenColor = nullptr;
	QPen *drawPen = nullptr;
	int fontMetricsHeight;
	int fontMetricsAscent;

protected:
	bool deleteResource( ) override;

public:
	AppRenderImage( );

	~AppRenderImage( ) override;

	bool init( ) override;

	virtual const QFont * getFont( ) const;

	virtual const QFontMetrics * getFontMetrics( ) const;

	virtual bool renderTxt( QImage &result_render_image, const QString &render_txt ) const;

	virtual bool renderWidget( QImage &result_render_image, QWidget *render_widget ) const;
};
#endif // APPRENDERIMAGE_H_H_HEAD__FILE__
