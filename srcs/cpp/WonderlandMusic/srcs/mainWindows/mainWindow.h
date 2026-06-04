#ifndef MAINWINDOW_H_H_HEAD__FILE__
#define MAINWINDOW_H_H_HEAD__FILE__
#include <QMainWindow>

class MusicWidget;
class MainWindow : public QMainWindow {
	Q_OBJECT;
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
private:
	MusicWidget *musicWidget;
public:
	MainWindow( );
	~MainWindow( ) override;
};

#endif // MAINWINDOW_H_H_HEAD__FILE__
