#ifndef BASEOBJECT_H_H_HEAD__FILE__
#define BASEOBJECT_H_H_HEAD__FILE__

#include <QObject>
class BaseObject : public QObject {
	Q_OBJECT;
public:
	BaseObject( QObject *parent ) : QObject( parent ) { }
};

#endif // BASEOBJECT_H_H_HEAD__FILE__
