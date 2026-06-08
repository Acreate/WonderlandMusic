#ifndef BASEOBJECT_H_H_HEAD__FILE__
#define BASEOBJECT_H_H_HEAD__FILE__

#include <QObject>

#include "../baseClass.h"
class BaseObject : public QObject, public BaseClass {
	Q_OBJECT;
public:
	BaseObject( QObject *parent );
	BaseObject( );
};

#endif // BASEOBJECT_H_H_HEAD__FILE__
