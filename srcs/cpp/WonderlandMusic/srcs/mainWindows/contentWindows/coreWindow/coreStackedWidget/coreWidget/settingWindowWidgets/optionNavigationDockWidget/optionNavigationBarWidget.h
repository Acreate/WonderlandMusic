#ifndef OPTIONNAVIGATIONBARWIDGET_H_H_HEAD__FILE__
#define OPTIONNAVIGATIONBARWIDGET_H_H_HEAD__FILE__

#include <QWidget>

#include "../../../../../../../baseWidget/baseWidget.h"
class OptionNavigationDockWidget;
class OptionNavigationBarWidget : public BaseWidget {
	Q_OBJECT;
protected:
	OptionNavigationDockWidget *optionNavigationDockWidget;
public:
	OptionNavigationBarWidget( OptionNavigationDockWidget *parent );
};

#endif // OPTIONNAVIGATIONBARWIDGET_H_H_HEAD__FILE__
