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
protected:
	class Translate {
		friend class MainWindow;
		/// @brief 窗口对象名称
		QString appWindowObjectName;
		/// @brief 窗口标题名称
		QString windowTitleName;
	public:
		Translate( );
	} translate;
	/// @brief 缩放状态
	enum class ScaleStatus {
		None = 0, // 没有
		Top = 0x1, // 顶部
		Bottom = 0x10, // 底部
		Left = 0x100, // 左侧
		Right = 0x1000, // 右侧
		LeftTop = Left | Top, // 左上
		RightTop = Right | Top, // 右上
		LeftBottom = Left | Bottom, // 左下
		RightBottom = Right | Bottom, // 右下
	};
protected:
	/// @brief 顶部工具
	TopToolDockWidget *topToolDockWidget;
	/// @brief 功能面板
	FunctionDockWidget *functionDockWidget;
	/// @brief 内容面板
	ContentWindow *contentWindow;
	/// @brief 缩放检测许可
	bool scalePermission;
	/// @brief 缩放状态
	ScaleStatus scaleStatus;
	/// @brief 当前宽度
	int currenWidth;
	/// @brief 当前高度
	int currentHeight;
	/// @brief 放大缩小检测边缘大小
	int checkScaleMargin;
public:
	MainWindow( );
	~MainWindow( ) override;
protected:
	void resizeEvent( QResizeEvent *event ) override;
	void enterEvent( QEnterEvent *event ) override;
	void leaveEvent( QEvent *event ) override;
	void mouseMoveEvent( QMouseEvent *event ) override;
	void mousePressEvent( QMouseEvent *event ) override;
	void mouseReleaseEvent( QMouseEvent *event ) override;
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
