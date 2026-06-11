#ifndef MUSICLISTTOPWIDGET_H_H_HEAD__FILE__
#define MUSICLISTTOPWIDGET_H_H_HEAD__FILE__

#include <base/baseWidget/baseWidget.h>
class FontSize;
class MusicListTopWidget : public BaseWidget {
	Q_OBJECT;
protected:
	/// @brief 音乐名称项
	QLabel *musicNameItem;
	/// @brief 音乐主唱项
	QLabel *musicSingerItem;
	/// @brief 音乐播放时长项
	QLabel *musicPlayerTimeItem;
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
