#ifndef PLAYERDOCKWIDGET_H_H_HEAD__FILE__
#define PLAYERDOCKWIDGET_H_H_HEAD__FILE__

#include <QDockWidget>
#include <macro/eventMacroDefine.h>
class PlayerWidget;
class QPushButton;
class ContentWindow;

class Event_Default_Event_Info_Type_Name( PlayerWidget );

class PlayerDockWidget : public QDockWidget {
	friend class Event_Default_Event_Class_Type_Name( PlayerWidget );
	Q_OBJECT;
protected:
	ContentWindow *contentWindow;
	PlayerWidget *playerWidget;
public:
	PlayerDockWidget( ContentWindow *parent );
	virtual Event_Default_Receive_Call_Function( PlayerWidget );
};

#define PlayerDockWidgetEventTypeName Event_Default_Event_Info_Type_Name( PlayerDockWidget )
class PlayerDockWidgetEventTypeName {
public:
	enum class EventType {
		None,
		Player,
		Pause,
		Next_Track,
		Previous_Track,
	};
protected:
	EventType eventType;
public:
	virtual ~PlayerDockWidgetEventInfo( ) = default;
	PlayerDockWidgetEventInfo( const EventType event_type )
		: eventType( event_type ) { }
	virtual EventType getEventType( ) const { return eventType; }
};

Event_Define_Event_Class_type( PlayerWidget, PlayerDockWidget );
#endif // PLAYERDOCKWIDGET_H_H_HEAD__FILE__
