#ifndef MAINWINDOW_H_H_HEAD__FILE__
#define MAINWINDOW_H_H_HEAD__FILE__

#include "../base/baseWindow/baseMainWindow.h"

class ApplicationInstance;
class ApplicationEvenTrigger;
class ContentWindow;
class FunctionDockWidget;
class TopToolDockWidget;
class MainWindow : public BaseMainWindow {
	Q_OBJECT;
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
	/// @brief 翻译
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
};
#include <macro/eventMacroDefine.h>
class Event_Default_Event_Info_Type_Name( MainWindow ) {
public:
	enum class EventType {
		None,
		Close
	};
protected:
	EventType eventType;
public:
	virtual ~MainWindowEventInfo( ) = default;
	MainWindowEventInfo( const EventType event_type )
		: eventType( event_type ) { }
	virtual EventType getEventType( ) const { return eventType; }
};
#endif // MAINWINDOW_H_H_HEAD__FILE__
