#ifndef RENDER_H_H_HEAD__FILE__
#define RENDER_H_H_HEAD__FILE__
#include <qpoint.h>
#include <qtypes.h>

class QPainter;
class QFontMetrics;
class QFont;
class QColor;
class QPoint;
class QImage;
class QString;

class StringFontSize {
protected:
	int ascent;
	int height;
	int horizontalAdvance;
public:
	virtual ~StringFontSize( ) { }
	StringFontSize( int ascent, int height, int horizontal_advance )
		: ascent( ascent ),
		height( height ),
		horizontalAdvance( horizontal_advance ) { }
	StringFontSize( const StringFontSize &other )
		: ascent { other.ascent },
		height { other.height },
		horizontalAdvance { other.horizontalAdvance } { }
	StringFontSize( ) : ascent( 0 ), horizontalAdvance( 0 ), height( 0 ) { }
	StringFontSize & operator=( const StringFontSize &other ) {
		if( this == &other )
			return *this;
		ascent = other.ascent;
		height = other.height;
		horizontalAdvance = other.horizontalAdvance;
		return *this;
	}
	virtual int getAscent( ) const { return ascent; }
	virtual int getHeight( ) const { return height; }
	virtual int getHorizontalAdvance( ) const { return horizontalAdvance; }
	virtual int getWidth( ) const { return horizontalAdvance; }
};

class FontRender {
private:
	StringFontSize *fontSize;
	QString *txt;
	QImage *renderBuff;
	qint64 stringLength;
	bool isRender;
public:
	FontRender( );
	FontRender( const QString &txt );
	FontRender( const QString &txt, bool is_render );
	virtual void setTxt( const QString &txt );
	virtual const QImage * const getRenderBuff( ) const;
	virtual const QString & getTxt( ) const;
	virtual const StringFontSize * const getTxtFontSize( ) const;
	virtual ~FontRender( );
	virtual bool drawTarget( QPainter *painter_ptr, const int &x, const int &y );
	virtual bool drawTarget( QPainter *painter_ptr, const QPoint &offset ) {
		return drawTarget( painter_ptr, offset.x( ), offset.y( ) );
	}
	virtual bool drawTarget( QPainter *painter_ptr ) {
		return drawTarget( painter_ptr, 0, 0 );
	}
};

/// @brief 图像渲染
class Render {
	friend class ApplicationInstance;
protected:
	virtual ~Render( ) = default;
public:
	/// @brief 获取默认的字体
	/// @return 字体
	virtual const QFont & getFont( ) const = 0;
	/// @brief 检测字符串的渲染字体宽高
	/// @param txt 检测字体
	/// @return 宽高
	virtual const StringFontSize getTxtSize( const QString &txt ) = 0;
	/// @brief 检测字符串的渲染字体宽高
	/// @param font 使用字体
	/// @param txt 检测字体
	/// @return 宽高
	virtual const StringFontSize getTxtSize( const QFont &font, const QString &txt ) = 0;
	/// @brief 检测字符串的渲染字体宽高
	/// @param font_metrics 使用字体信息
	/// @param txt 检测字体
	/// @return 宽高
	virtual const StringFontSize getTxtSize( const QFontMetrics &font_metrics, const QString &txt ) = 0;
	/// @brief 渲染字符串到页面
	/// @param result_image 目标页面，同时用于返回
	/// @param text 字符串
	/// @return 失败返回 false
	virtual bool renderTextImage( QImage &result_image, const QString &text ) = 0;
	/// @brief 渲染字符串到页面
	/// @param result_image 目标页面，同时用于返回
	/// @param text 字符串
	/// @param draw_color 字体颜色
	/// @return 失败返回 false
	virtual bool renderTextImage( QImage &result_image, const QString &text, const QColor &draw_color ) = 0;
	/// @brief 渲染字符串到页面
	/// @param result_image 目标页面，同时用于返回
	/// @param text 字符串
	/// @param draw_font 绘制字体
	/// @return 失败返回 false
	virtual bool renderTextImage( QImage &result_image, const QString &text, const QFont &draw_font ) = 0;
	/// @brief 渲染字符串到页面
	/// @param result_image 目标页面，同时用于返回
	/// @param text 字符串
	/// @param draw_font 绘制字体
	/// @param draw_color 字体颜色
	/// @return 失败返回 false
	virtual bool renderTextImage( QImage &result_image, const QString &text, const QFont &draw_font, const QColor &draw_color ) = 0;
	/// @brief 重叠图像
	/// @param result_image 底层图像，同时用于返回
	/// @param top_image 上层图像
	/// @return 失败返回 false
	virtual bool renderOverlapImage( QImage &result_image, const QImage &top_image ) = 0;
	/// @brief 扩张图像
	/// @param result_image 被扩张的图像，同时用于返回
	/// @param expand_image 拷贝的目标图像
	/// @param pos 拷贝原始坐标
	/// @return 失败返回 false
	virtual bool renderExpandImage( QImage &result_image, const QImage &expand_image, const QPoint &pos ) = 0;
	/// @brief 填充颜色
	/// @param result_image 被填充的图像，同时用于返回
	/// @param color 填充颜色
	/// @return 失败返回 false
	virtual bool renderColorImage( QImage &result_image, const QColor &color ) = 0;
	/// @brief 替换图像中的颜色
	/// @param result_image 替换图像
	/// @param old_color 被替换的颜色
	/// @param new_color 新的颜色
	/// @return 失败返回 false
	virtual bool renderColorReplaceColorImage( QImage &result_image, const QColor &old_color, const QColor &new_color ) =0;
};

#endif // RENDER_H_H_HEAD__FILE__
