#ifndef BASEWIDGET_H_H_HEAD__FILE__
#define BASEWIDGET_H_H_HEAD__FILE__

#include <QWidget>

#include "../baseClass.h"
class ApplicationInstance;
class ApplicationEvenTrigger;
class BaseWidget : public QWidget, public BaseClass {
	Q_OBJECT;
public:
	BaseWidget( QWidget *parent );
	BaseWidget( );
};

#endif // BASEWIDGET_H_H_HEAD__FILE__
