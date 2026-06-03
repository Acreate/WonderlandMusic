#ifndef MAINWINDOW_H_H_HEAD__FILE__
#define MAINWINDOW_H_H_HEAD__FILE__
#include <QMainWindow>

class MusicWidget;
class MainWindow : public QMainWindow {
	Q_OBJECT;
private:
	MusicWidget *musicWidget;
public:
	MainWindow( );
	~MainWindow( ) override;
};

#endif // MAINWINDOW_H_H_HEAD__FILE__
