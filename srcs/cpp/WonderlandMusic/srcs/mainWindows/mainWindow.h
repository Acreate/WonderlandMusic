#ifndef MAINWINDOW_H_H_HEAD__FILE__
#define MAINWINDOW_H_H_HEAD__FILE__
#include <QMainWindow>

class TopToolDockWidget;
class ContentWindow;
class FunctionDockWidget;
class PlayerDockWidget;
class FunctionEvent;
class ToolEvent;
class MainWindow : public QMainWindow {
	Q_OBJECT;
	friend class FunctionEvent;
	friend class ToolEvent;
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
	virtual bool functionEvent( FunctionDockWidget *event_dock_widget ) {
		return false;
	}
	virtual bool toolEvent( TopToolDockWidget *event_dock_widget ) {
		return false;
	}
};

class FunctionEvent {
	friend class FunctionDockWidget;
	static bool functionEvent( MainWindow reveive_window, FunctionDockWidget *event_dock_widget ) {
		return reveive_window.functionEvent( event_dock_widget );
	}
};

class ToolEvent {
	friend class TopToolDockWidget;
	static bool functionEvent( MainWindow reveive_window, TopToolDockWidget *event_dock_widget ) {
		return reveive_window.toolEvent( event_dock_widget );
	}
};

#endif // MAINWINDOW_H_H_HEAD__FILE__
