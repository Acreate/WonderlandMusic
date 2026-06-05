#ifndef MAINWINDOW_H_H_HEAD__FILE__
#define MAINWINDOW_H_H_HEAD__FILE__
#include <QMainWindow>

class TopToolDockEventInfo;
class FunctionDockEventInfo;
class TopToolEventInfo;
class TopToolDockWidget;
class ContentWindow;
class FunctionDockWidget;
class PlayerDockWidget;
class FunctionDockEvent;
class ToolTopToolDockEvent;
class MainWindow : public QMainWindow {
	Q_OBJECT;
	friend class FunctionDockEvent;
	friend class ToolTopToolDockEvent;
private:
	class Translate {
		friend class MainWindow;
		/// @brief 窗口对象名称
		QString appWindowObjectName;
		/// @brief 窗口标题名称
		QString windowTitleName;
	public:
		Translate( );
	} translate;
protected:
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
	virtual size_t triggerFunctionDockEvent( FunctionDockWidget *event_dock_widget, const FunctionDockEventInfo &function_dock_event_info ) {
		return false;
	}
	virtual size_t triggerTopToolDockEvent( TopToolDockWidget *event_dock_widget, const TopToolDockEventInfo &top_tool_event_info );
};

class FunctionDockEvent {
	friend class FunctionDockWidget;
	static size_t triggerFunctionDockEvent( MainWindow *reveive_window, FunctionDockWidget *event_dock_widget, const FunctionDockEventInfo &function_dock_event_info ) {
		return reveive_window->triggerFunctionDockEvent( event_dock_widget, function_dock_event_info );
	}
};

class ToolTopToolDockEvent {
	friend class TopToolDockWidget;
	static size_t triggerTopToolDockEvent( MainWindow *reveive_window, TopToolDockWidget *event_dock_widget, const TopToolDockEventInfo &top_tool_event_info ) {
		return reveive_window->triggerTopToolDockEvent( event_dock_widget, top_tool_event_info );
	}
};

#endif // MAINWINDOW_H_H_HEAD__FILE__
