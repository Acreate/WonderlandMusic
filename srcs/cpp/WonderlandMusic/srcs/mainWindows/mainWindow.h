#ifndef MAINWINDOW_H_H_HEAD__FILE__
#define MAINWINDOW_H_H_HEAD__FILE__
#include <QMainWindow>

#include "../event/eventMacroDefine.h"

#define FunctionDockEventClassName Event_Default_ClassName( FunctionDockWidget )
#define FunctionDockEventDefaultEventCallFunction Event_Default_Receive_Call_Function( FunctionDockWidget )
#define FunctionDockEventDefineClass Event_Define_Event_Class_type( FunctionDockWidget, MainWindow )
class Event_Default_Event_Info_Type_Name( FunctionDockWidget );

#define TopToolDockEventClassName Event_Default_ClassName( TopToolDockWidget )
#define TopToolDockEventDefaultEventCallFunction Event_Default_Receive_Call_Function( TopToolDockWidget )
#define TopToolDockEventDefineClass Event_Define_Event_Class_type( TopToolDockWidget, MainWindow)
class Event_Default_Event_Info_Type_Name( TopToolDockWidget );



#define ContentWindowEventClassName Event_Default_ClassName( ContentWindow )
#define ContentWindowEventDefaultEventCallFunction Event_Default_Receive_Call_Function( ContentWindow )
#define ContentWindowEventDefineClass Event_Define_Event_Class_type( ContentWindow, MainWindow)
class Event_Default_Event_Info_Type_Name( ContentWindow );

class ContentWindow;
class FunctionDockWidget;
class TopToolDockWidget;
class MainWindow : public QMainWindow {
	Q_OBJECT;
	friend class FunctionDockEventClassName;
	friend class TopToolDockEventClassName;
	friend class ContentWindowEventClassName;
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
	virtual FunctionDockEventDefaultEventCallFunction;
	virtual TopToolDockEventDefaultEventCallFunction;
	virtual ContentWindowEventDefaultEventCallFunction;
};

FunctionDockEventDefineClass;
TopToolDockEventDefineClass;
ContentWindowEventDefineClass;


#endif // MAINWINDOW_H_H_HEAD__FILE__
