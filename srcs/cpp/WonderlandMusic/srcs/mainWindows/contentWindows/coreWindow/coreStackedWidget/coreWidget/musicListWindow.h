#ifndef MUSICLISTWINDOW_H_H_HEAD__FILE__
#define MUSICLISTWINDOW_H_H_HEAD__FILE__

#include <QMainWindow>

class CoreStackedWidget;
class MusicListWindow : public QMainWindow {
	Q_OBJECT;
protected:
	CoreStackedWidget *coreStackedWidget;
public:
	MusicListWindow( CoreStackedWidget *parent );
protected:
	void paintEvent( QPaintEvent *event ) override;
};
#endif // MUSICLISTWINDOW_H_H_HEAD__FILE__
