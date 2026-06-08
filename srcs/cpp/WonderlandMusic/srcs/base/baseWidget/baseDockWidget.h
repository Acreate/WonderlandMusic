#ifndef BASEDOCKWIDGET_H_H_HEAD__FILE__
#define BASEDOCKWIDGET_H_H_HEAD__FILE__

#include <QDockWidget>

#include "../baseClass.h"
class BaseDockWidget : public QDockWidget, public BaseClass {
	Q_OBJECT;
public:
	BaseDockWidget( QWidget *parent );
	BaseDockWidget( );
};

#endif // BASEDOCKWIDGET_H_H_HEAD__FILE__
