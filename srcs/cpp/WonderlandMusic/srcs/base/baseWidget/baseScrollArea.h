#ifndef BASESCROLLAREA_H_H_HEAD__FILE__
#define BASESCROLLAREA_H_H_HEAD__FILE__

#include <QScrollArea>

#include "../baseClass.h"
class BaseScrollArea : public QScrollArea, public BaseClass {
	Q_OBJECT;
public:
	BaseScrollArea( QWidget *parent );
	BaseScrollArea( );
};

#endif // BASESCROLLAREA_H_H_HEAD__FILE__
