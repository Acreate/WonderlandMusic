#ifndef APPFUNCTIONWIDGET_H_H_HEAD__FILE__
#define APPFUNCTIONWIDGET_H_H_HEAD__FILE__

#include <QWidget>

class AppFunctionWidgetItemWidget;
class AppFunctionItem;
class AppFunctionWidgetClickEvent;
/// @brief 软件功能面板
class AppFunctionWidget : public QWidget {
	Q_OBJECT;
	friend class AppFunctionWidgetClickEvent;
public:
	AppFunctionWidget( QWidget *parent = nullptr );
protected:
	void paintEvent( QPaintEvent *event ) override;

	virtual bool clinkItem( AppFunctionWidgetItemWidget *item, Qt::MouseButton mouse_button, const QPoint &pos );
};

class AppFunctionWidgetClickEvent {
	friend class AppFunctionWidgetItemWidget;
	/// @brief 点击事件
	/// @param sender_event 发送目标
	/// @param item 点击选项
	/// @param mouse_button 点击的主要按键
	/// @param pos 点击坐标
	static bool clinkItem( AppFunctionWidget *sender_event, AppFunctionWidgetItemWidget *item, Qt::MouseButton mouse_button, const QPoint &pos ) {
		if( sender_event == nullptr )
			return false;
		return sender_event->clinkItem( item, mouse_button, pos );
	}
};
#endif // APPFUNCTIONWIDGET_H_H_HEAD__FILE__
