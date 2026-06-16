#ifndef PLAYERDOCKWIDGET_H_H_HEAD__FILE__
#define PLAYERDOCKWIDGET_H_H_HEAD__FILE__

#include <macro/eventMacroDefine.h>

#include <base/baseWidget/baseDockWidget.h>
class PlayerWidget;
class QPushButton;
class ContentWindow;

class PlayerDockWidget : public BaseDockWidget {
	Q_OBJECT;
protected:
	ContentWindow *contentWindow;
	PlayerWidget *playerWidget;
public:
	PlayerDockWidget( ContentWindow *parent );
};

#define PlayerDockWidgetEventTypeName Event_Define_Event_Info_Type_Name( PlayerDockWidget )
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

#endif // PLAYERDOCKWIDGET_H_H_HEAD__FILE__
