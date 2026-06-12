#ifndef MUSICLISTTOPWIDGET_H_H_HEAD__FILE__
#define MUSICLISTTOPWIDGET_H_H_HEAD__FILE__

#include <base/baseWidget/baseWidget.h>
class FontRender;
class StringFontSize;
class MusicListTopWidget : public BaseWidget {
	Q_OBJECT;
protected:
	/// @brief 音乐名称项
	FontRender *musicNameItem;
	/// @brief 名称长度
	int musicNameItemWidth;
	/// @brief 音乐主唱项
	FontRender *musicSingerItem;
	/// @brief 主唱长度
	int musicSingerItemWidth;
	/// @brief 音乐播放时长项
	FontRender *musicPlayerTimeItem;
	/// @brief 播放时长宽度
	int musicPlayerTimeItemWidth;
	/// @brief 辅助计算偏移 x
	int drawOffsetX;
private:
	void initItemSize( const FontRender &font_render, int &result_width, int &result_height ) const;
public:
	MusicListTopWidget( QWidget *parent );
	virtual int getMusicNameItemWidth( ) const;
	virtual int getMusicSingerItemWidth( ) const;
	virtual int getMusicPlayerTimeItemWidth( ) const;
protected:
	void resizeEvent( QResizeEvent *event ) override;
	void paintEvent( QPaintEvent *event ) override;
};

#endif // MUSICLISTTOPWIDGET_H_H_HEAD__FILE__
