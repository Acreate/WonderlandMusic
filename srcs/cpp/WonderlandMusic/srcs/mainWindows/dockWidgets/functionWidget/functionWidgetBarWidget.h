#ifndef FUNCTIONWIDGETBARWIDGET_H_H_HEAD__FILE__
#define FUNCTIONWIDGETBARWIDGET_H_H_HEAD__FILE__

#include <QWidget>

#include "../../../baseWidget/baseWidget.h"
class FunctionDockWidget;
class FunctionWidgetBarWidget : public BaseWidget {
	Q_OBJECT;
protected:
	FunctionDockWidget *functionDockWidget;
public:
	FunctionWidgetBarWidget( FunctionDockWidget *parent );
};

#endif // FUNCTIONWIDGETBARWIDGET_H_H_HEAD__FILE__
