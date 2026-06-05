#ifndef TOPTOOLDOCKWIDGET_H_H_HEAD__FILE__
#define TOPTOOLDOCKWIDGET_H_H_HEAD__FILE__

#include <QDockWidget>
class TopToolWidget;
class MainWindow;
class TopToolDockWidget : public QDockWidget {
	Q_OBJECT;
protected:
	MainWindow *mainWindow;
	TopToolWidget *topToolWidget;
public:
	TopToolDockWidget( MainWindow *parent );
};

#endif // TOPTOOLDOCKWIDGET_H_H_HEAD__FILE__
