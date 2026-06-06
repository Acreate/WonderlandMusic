#ifndef PLAYERDOCKWIDGET_H_H_HEAD__FILE__
#define PLAYERDOCKWIDGET_H_H_HEAD__FILE__

#include <QDockWidget>
class ContentWindow;

class PlayerDockWidget : public QDockWidget {
	Q_OBJECT;
protected:
	ContentWindow *contentWindow;
public:
	PlayerDockWidget( ContentWindow *parent );
protected:
	void paintEvent( QPaintEvent *event ) override;
};

#include <event/eventMacroDefine.h>
#define PlayerDockWidgetEventTypeName Event_Default_Event_Info_Type_Name( PlayerDockWidget )
class PlayerDockWidgetEventTypeName {

};
#endif // PLAYERDOCKWIDGET_H_H_HEAD__FILE__
