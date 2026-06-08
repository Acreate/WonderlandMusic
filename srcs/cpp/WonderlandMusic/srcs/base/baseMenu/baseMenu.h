#ifndef BASEMENU_H_H_HEAD__FILE__
#define BASEMENU_H_H_HEAD__FILE__

#include <QMenu>

#include "../baseClass.h"
class BaseMenu : public QMenu, public BaseClass {
	Q_OBJECT;
public:
	BaseMenu( QWidget *parent );
	BaseMenu( const QString &titile, QWidget *parent );
	BaseMenu( const QString &titile );
	BaseMenu( );
};

#endif // BASEMENU_H_H_HEAD__FILE__
