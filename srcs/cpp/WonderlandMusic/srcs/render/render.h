#ifndef RENDER_H_H_HEAD__FILE__
#define RENDER_H_H_HEAD__FILE__

class QFont;
class QColor;
class QPoint;
class QImage;
class QString;
/// @brief 图像渲染
class Render {
	friend class Application;
protected:
	virtual ~Render( ) = default;
public:
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
