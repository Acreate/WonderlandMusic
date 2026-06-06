#ifndef MAINWINDOW_H_H_HEAD__FILE__
#define MAINWINDOW_H_H_HEAD__FILE__
#include <QMainWindow>

#include "../event/eventMacroDefine.h"

class TopToolDockEventInfo;
class FunctionDockEventInfo;
class TopToolEventInfo;
class TopToolDockWidget;
class ContentWindow;
class FunctionDockWidget;
class PlayerDockWidget;
class FunctionDockEvent;
class ToolTopToolDockEvent;
class MainWindow;

#define FunctionDockEventClassName Event_Default_ClassName( FunctionDock )
#define FunctionDockEventTrigger Event_Default_Event_Call_Function_Name(  FunctionDock )
#define FunctionDockEventDefineClass Event_Define_Event_Class_type( FunctionDock, MainWindow, FunctionDockWidget, FunctionDockEventInfo )

#define ToolTopToolDockEventClass Event_Default_ClassName( TopToolDock )
#define TopToolDockEventTrigger Event_Default_Event_Call_Function_Name(  TopToolDock )
#define ToolTopToolDockEventDefineClass Event_Define_Event_Class_type( TopToolDock, MainWindow, TopToolDockWidget, TopToolDockEventInfo )

class MainWindow : public QMainWindow {
	Q_OBJECT;
	friend class FunctionDockEventClassName;
	friend class ToolTopToolDockEventClass;
public:
	class Translate {
		friend class MainWindow;
		/// @brief 窗口对象名称
		QString appWindowObjectName;
		/// @brief 窗口标题名称
		QString windowTitleName;
	public:
		Translate( );
	};
protected:
	Translate translate;
	/// @brief 顶部工具
	TopToolDockWidget *topToolDockWidget;
	/// @brief 功能面板
	FunctionDockWidget *functionDockWidget;
	/// @brief 内容面板
	ContentWindow *contentWindow;
public:
	MainWindow( );
	~MainWindow( ) override;
private:
	virtual size_t FunctionDockEventTrigger( FunctionDockWidget *event_dock_widget, const FunctionDockEventInfo &function_dock_event_info );
	virtual size_t TopToolDockEventTrigger( TopToolDockWidget *event_dock_widget, const TopToolDockEventInfo &top_tool_event_info );
};

FunctionDockEventDefineClass;

ToolTopToolDockEventDefineClass;

#endif // MAINWINDOW_H_H_HEAD__FILE__
