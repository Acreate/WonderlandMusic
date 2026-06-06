#ifndef FUNCTIONWIDGETBARWIDGET_H_H_HEAD__FILE__
#define FUNCTIONWIDGETBARWIDGET_H_H_HEAD__FILE__

#include <QWidget>
class FunctionDockWidget;
class FunctionWidgetBarWidget : public QWidget {
	Q_OBJECT;
protected:
	FunctionDockWidget *functionDockWidget;
public:
	FunctionWidgetBarWidget( FunctionDockWidget *parent );
};

#endif // FUNCTIONWIDGETBARWIDGET_H_H_HEAD__FILE__
