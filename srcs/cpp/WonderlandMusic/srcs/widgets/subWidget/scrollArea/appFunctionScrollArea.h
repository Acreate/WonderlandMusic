#ifndef APPFUNCTIONSCROLLAREA_H_H_HEAD__FILE__
#define APPFUNCTIONSCROLLAREA_H_H_HEAD__FILE__

#include <QScrollArea>
class AppFunctionWidget;
class AppFunctionScrollArea : public QScrollArea {
	Q_OBJECT;
protected:
	AppFunctionWidget* appFunctionWidget;
public:
	AppFunctionScrollArea( QWidget *parent );
};

#endif // APPFUNCTIONSCROLLAREA_H_H_HEAD__FILE__
