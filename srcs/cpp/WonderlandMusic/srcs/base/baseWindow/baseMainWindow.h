#ifndef BASEMAINWINDOW_H_H_HEAD__FILE__
#define BASEMAINWINDOW_H_H_HEAD__FILE__

#include <QMainWindow>

#include "../baseClass.h"
class BaseMainWindow : public QMainWindow, public BaseClass {
	Q_OBJECT;
public:
	BaseMainWindow( QWidget *parent );
	BaseMainWindow(  );

};

#endif // BASEMAINWINDOW_H_H_HEAD__FILE__
