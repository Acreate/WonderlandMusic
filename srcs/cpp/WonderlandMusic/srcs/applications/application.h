#ifndef APPLICATION_H_H_HEAD__FILE__
#define APPLICATION_H_H_HEAD__FILE__

#include <QApplication>
class MainWindow;
class Application : public QApplication {
	Q_OBJECT;
public:
	Application( int &argc, char **const argv, const int i = ApplicationFlags );
	~Application( ) override;
	bool notify( QObject *object, QEvent *event ) override;
private:
	/// @brief 主要先显示的窗口
	MainWindow *mainWindowPtr;
	/// @brief 是否第一次显示
	bool firstShow;
public:
	/// @brief 获取配置的主要窗口
	/// @return 主要窗口
	virtual MainWindow * getMainWindowPtr( ) const { return mainWindowPtr; }
	/// @brief 设置主要窗口，未配置该项时，窗口已经显示，则不会调用 firstMainWindowShow
	/// @param main_window_ptr 配置的主要窗口
	virtual void setMainWindowPtr( MainWindow *main_window_ptr );
private:
	/// @brief 第一次显示主要窗口时调用该函数
	/// @param first_show_main_window 调用的主要窗口
	void firstMainWindowShow( MainWindow *first_show_main_window );
};

#endif // APPLICATION_H_H_HEAD__FILE__
