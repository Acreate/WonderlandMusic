#ifndef FUNCTIONDOCKWIDGET_H_H_HEAD__FILE__
#define FUNCTIONDOCKWIDGET_H_H_HEAD__FILE__

#include <QDockWidget>
class MainWindow;
/// @brief 功能面板
class FunctionDockWidget : public QDockWidget {
	Q_OBJECT;
protected:
	MainWindow *mainWindow;
public:
	FunctionDockWidget( MainWindow *parent );
protected:
	void paintEvent( QPaintEvent *event ) override;
};

#endif // FUNCTIONDOCKWIDGET_H_H_HEAD__FILE__
