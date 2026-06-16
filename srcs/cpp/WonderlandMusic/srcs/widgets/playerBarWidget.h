#ifndef PLAYERBARWIDGET_H_H_HEAD__FILE__
#define PLAYERBARWIDGET_H_H_HEAD__FILE__

#include <base/baseWidget/baseWidget.h>
class PlayerDockWidget;
class PlayerBarWidget : public BaseWidget {
	Q_OBJECT;
protected:
	PlayerDockWidget *playerDockWidget;
public:
	PlayerBarWidget( PlayerDockWidget *parent );
};

#endif // PLAYERBARWIDGET_H_H_HEAD__FILE__
