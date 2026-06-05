#ifndef MUSICPLAYERBUTTONWIDGETITEMWIDGET_H_H_HEAD__FILE__
#define MUSICPLAYERBUTTONWIDGETITEMWIDGET_H_H_HEAD__FILE__


#include <QWidget>
class MusicPlayerButtonWidgetItemWidget : public QWidget {
	Q_OBJECT;
public:
	MusicPlayerButtonWidgetItemWidget( QWidget *parent ) : QWidget( parent ) { }
protected:
	void mouseReleaseEvent( QMouseEvent *event ) override;
Q_SIGNALS:
	/// @brief 点击事件
	/// @param item 点击选项
	/// @param mouse_button 点击的主要按键
	/// @param pos 点击坐标
	void clinkItem( MusicPlayerButtonWidgetItemWidget *item, Qt::MouseButton mouse_button, const QPoint &pos );
};

#endif // MUSICPLAYERBUTTONWIDGETITEMWIDGET_H_H_HEAD__FILE__
