#ifndef FUNCTIONDOCKWIDGET_H_H_HEAD__FILE__
#define FUNCTIONDOCKWIDGET_H_H_HEAD__FILE__

#include <QDockWidget>

class FunctionWidget;
class MainWindow;

// 事件头文件
#include <macro/eventMacroDefine.h>
/// @brief 展开事件类名
#define FunctionWidgetEventClassName Event_Default_Event_Class_Type_Name( FunctionWidget )
/// @brief 展开事件发送函数声明
#define FunctionWidgetDefaultEventCallFunction Event_Default_Receive_Call_Function( FunctionWidget )
/// @brief 展开定义事件类
#define FunctionWidgetEventDefineClass Event_Define_Event_Class_type( FunctionWidget, FunctionDockWidget)
/// @brief 展开声明事件信息类型
class Event_Default_Event_Info_Type_Name( FunctionWidget );

/// @brief 功能面板
class FunctionDockWidget : public QDockWidget {
	friend class FunctionWidgetEventClassName;
	Q_OBJECT;
protected:
	MainWindow *mainWindow;
	FunctionWidget *functionWidget;
public:
	FunctionDockWidget( MainWindow *parent );
protected:
	void paintEvent( QPaintEvent *event ) override;
private:
	virtual FunctionWidgetDefaultEventCallFunction;
};

#define FunctionDockWidgetEventTypeName Event_Default_Event_Info_Type_Name( FunctionDockWidget )
class FunctionDockWidgetEventTypeName {
public:
	enum class EventType {
		None,
		Show_Music,
		Show_Setting,
	};
protected:
	EventType type;
public:
	virtual ~FunctionDockWidgetEventTypeName( ) = default;
	FunctionDockWidgetEventTypeName( const EventType type )
		: type( type ) { }
	virtual EventType getType( ) const { return type; }
};

FunctionWidgetEventDefineClass;
#endif // FUNCTIONDOCKWIDGET_H_H_HEAD__FILE__
