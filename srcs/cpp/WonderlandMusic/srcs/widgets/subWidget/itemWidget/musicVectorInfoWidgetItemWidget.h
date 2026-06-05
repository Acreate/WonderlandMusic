#ifndef MUSICVECTORINFOWIDGETITEMWIDGET_H_H_HEAD__FILE__
#define MUSICVECTORINFOWIDGETITEMWIDGET_H_H_HEAD__FILE__

#include <QWidget>
class MusicVectorInfoWidgetItemWidget : public QWidget {
	Q_OBJECT;
public:
	MusicVectorInfoWidgetItemWidget( QWidget *parent ) : QWidget( parent ) { }
protected:
	void mouseReleaseEvent( QMouseEvent *event ) override;
Q_SIGNALS:
	/// @brief 点击事件
	/// @param item 点击选项
	/// @param mouse_button 点击的主要按键
	/// @param pos 点击坐标
	void clinkItem( MusicVectorInfoWidgetItemWidget *item, Qt::MouseButton mouse_button, const QPoint &pos );
};

#endif // MUSICVECTORINFOWIDGETITEMWIDGET_H_H_HEAD__FILE__
