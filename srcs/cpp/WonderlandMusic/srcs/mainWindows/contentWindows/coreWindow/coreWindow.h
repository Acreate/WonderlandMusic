#ifndef COREWINDOW_H_H_HEAD__FILE__
#define COREWINDOW_H_H_HEAD__FILE__

#include <QMainWindow>
class CoreStackedWidget;
class CoreStackedWidgeEventInfo;
class ContentWindow;

// 事件头文件
#include <event/eventMacroDefine.h>
/// @brief 展开事件类名
#define CoreStackedWidgetEventClassName Event_Default_ClassName( CoreStackedWidget )
/// @brief 展开事件发送函数声明
#define CoreStackedWidgetDefaultEventCallFunction Event_Default_Receive_Call_Function( CoreStackedWidget )
/// @brief 展开定义事件类
#define CoreStackedWidgetEventDefineClass Event_Define_Event_Class_type( CoreStackedWidget, CoreWindow )
class Event_Default_Event_Info_Type_Name( CoreStackedWidget );

class CoreWindow : public QMainWindow {
	friend class CoreStackedWidgetEventClassName;
	Q_OBJECT;
protected:
	/// @brief 父窗口
	ContentWindow *contentWindow;
	/// @brief 堆叠的窗口
	CoreStackedWidget *coreStackedWidget;
public:
	CoreWindow( ContentWindow *parent );
protected:
	void paintEvent( QPaintEvent *event ) override;
private:
	virtual CoreStackedWidgetDefaultEventCallFunction;
};

#define CoreWindowEventTypeName Event_Default_Event_Info_Type_Name( CoreWindow )
class CoreWindowEventTypeName {

};
CoreStackedWidgetEventDefineClass;

#endif // COREWINDOW_H_H_HEAD__FILE__
