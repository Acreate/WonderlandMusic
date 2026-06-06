#ifndef OPTIONNAVIGATIONBARWIDGET_H_H_HEAD__FILE__
#define OPTIONNAVIGATIONBARWIDGET_H_H_HEAD__FILE__

#include <QWidget>
class OptionNavigationDockWidget;
class OptionNavigationBarWidget : public QWidget {
	Q_OBJECT;
protected:
	OptionNavigationDockWidget *optionNavigationDockWidget;
public:
	OptionNavigationBarWidget( OptionNavigationDockWidget *parent );
};

#endif // OPTIONNAVIGATIONBARWIDGET_H_H_HEAD__FILE__
