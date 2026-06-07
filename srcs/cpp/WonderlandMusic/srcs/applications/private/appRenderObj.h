#ifndef APPRENDEROBJ_H_H_HEAD__FILE__
#define APPRENDEROBJ_H_H_HEAD__FILE__

#include <render/render.h>

class QString;
class QPoint;
class QImage;
class AppRenderObj : public Render {
	friend class ApplicationInstance;
private:
	QFont *font;
	QColor *color;
private:
	AppRenderObj( const QFont &font, const QColor &color );
protected:
	~AppRenderObj( ) override;
public:
	bool renderTextImage( QImage &result_image, const QString &text ) override;
	bool renderTextImage( QImage &result_image, const QString &text, const QColor &draw_color ) override;
	bool renderTextImage( QImage &result_image, const QString &text, const QFont &draw_font ) override;
	bool renderTextImage( QImage &result_image, const QString &text, const QFont &draw_font, const QColor &draw_color ) override;
	bool renderOverlapImage( QImage &result_image, const QImage &top_image ) override;
	bool renderExpandImage( QImage &result_image, const QImage &expand_image, const QPoint &pos ) override;
	bool renderColorImage( QImage &result_image, const QColor &color ) override;
	bool renderColorReplaceColorImage( QImage &result_image, const QColor &old_color, const QColor &new_color ) override;
};

#endif // APPRENDEROBJ_H_H_HEAD__FILE__
