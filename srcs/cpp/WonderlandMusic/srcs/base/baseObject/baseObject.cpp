#include "baseObject.h"

#include <source_location>
#include <QDebug>
BaseObject::BaseObject( QObject *parent ) : QObject( parent ), BaseClass( ) {
}
BaseObject::BaseObject( ) : QObject( ), BaseClass( ) {
}
