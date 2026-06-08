#ifndef BASESTACKEDWIDGET_H_H_HEAD__FILE__
#define BASESTACKEDWIDGET_H_H_HEAD__FILE__

#include <QStackedWidget>

#include "../baseClass.h"
class BaseStackedWidget : public QStackedWidget, public BaseClass {
	Q_OBJECT;
public:
	BaseStackedWidget( QWidget *parent );
	BaseStackedWidget( );
};

#endif // BASESTACKEDWIDGET_H_H_HEAD__FILE__
