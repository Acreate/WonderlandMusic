#ifndef MAINWINDOW_H_H_HEAD__FILE__
#define MAINWINDOW_H_H_HEAD__FILE__
#include <QMainWindow>

class Application;
class ApplicationEvenTrigger;
class ContentWindow;
class FunctionDockWidget;
class TopToolDockWidget;
class MainWindow : public QMainWindow {
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
	/// @brief app 本身
	Application *application;
	/// @brief app 事件
	ApplicationEvenTrigger *applicationEvenTrigger;
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

#endif // MAINWINDOW_H_H_HEAD__FILE__
