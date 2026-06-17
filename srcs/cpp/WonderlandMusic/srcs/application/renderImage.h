#ifndef RENDERIMAGE_H_H_HEAD__FILE__
#define RENDERIMAGE_H_H_HEAD__FILE__

class QWidget;
class QPen;
class QColor;
class QString;
class QImage;
class QFontMetrics;
class QFont;
class RenderImage {
protected:
	QFont *font;
	QFontMetrics *fontMetrics;
	QColor *brackGroundColor;
	QColor *drawPenColor;
	QPen *drawPen;
	int fontMetricsHeight;
	int fontMetricsAscent;
public:
	RenderImage( );
	virtual ~RenderImage( );
	virtual bool init( );
	virtual const QFont * getFont( ) const;
	virtual const QFontMetrics * getFontMetrics( ) const;
	virtual bool renderTxt( QImage &result_render_image, const QString &render_txt ) const;
	virtual bool renderWidget( QImage &result_render_image, QWidget *render_widget ) const;
};

#endif // RENDERIMAGE_H_H_HEAD__FILE__
