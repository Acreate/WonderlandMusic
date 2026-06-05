#ifndef TOPTOOLDOCKWIDGET_H_H_HEAD__FILE__
#define TOPTOOLDOCKWIDGET_H_H_HEAD__FILE__

#include <QDockWidget>
class MainWindow;
class TopToolDockWidget : public QDockWidget {
	Q_OBJECT;
protected:
	MainWindow *mainWindow;
public:
	TopToolDockWidget( MainWindow *  parent );
protected:
	void paintEvent( QPaintEvent *event ) override;
};

#endif // TOPTOOLDOCKWIDGET_H_H_HEAD__FILE__
