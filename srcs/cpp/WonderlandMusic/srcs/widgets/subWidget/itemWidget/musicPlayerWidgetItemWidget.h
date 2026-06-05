#ifndef MUSICPLAYERWIDGETITEMWIDGET_H_H_HEAD__FILE__
#define MUSICPLAYERWIDGETITEMWIDGET_H_H_HEAD__FILE__

#include <QWidget>
class MusicPlayerWidgetItemWidget : public QWidget {
	Q_OBJECT;
public:
	MusicPlayerWidgetItemWidget( QWidget *parent ) : QWidget( parent ) { }
protected:
	void mouseReleaseEvent( QMouseEvent *event ) override;
Q_SIGNALS:
	/// @brief 点击事件
	/// @param item 点击选项
	/// @param mouse_button 点击的主要按键
	/// @param pos 点击坐标
	void clinkItem( MusicPlayerWidgetItemWidget *item, Qt::MouseButton mouse_button, const QPoint &pos );
};

#endif // MUSICPLAYERWIDGETITEMWIDGET_H_H_HEAD__FILE__
