#ifndef PLAYERBARWIDGET_H_H_HEAD__FILE__
#define PLAYERBARWIDGET_H_H_HEAD__FILE__

#include <QWidget>
class PlayerDockWidget;
class PlayerBarWidget : public QWidget {
	Q_OBJECT;
protected:
	PlayerDockWidget *playerDockWidget;
public:
	PlayerBarWidget( PlayerDockWidget *parent );
};

#endif // PLAYERBARWIDGET_H_H_HEAD__FILE__
