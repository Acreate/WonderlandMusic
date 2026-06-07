#ifndef CONTROLMUSICLISTMENU_H_H_HEAD__FILE__
#define CONTROLMUSICLISTMENU_H_H_HEAD__FILE__

class {

};

#include <QMenu>
class ControlMusicListMenu : public QMenu {
	Q_OBJECT;
public:
	ControlMusicListMenu( ) { }
	~ControlMusicListMenu( ) override;
};
#include <macro/eventMacroDefine.h>
class Event_Default_Event_Info_Type_Name( ControlMusicListMenu ) {
public:
	enum class EventType {
		None,
		Delete_This_Menu_Ptr
	};
protected:
	EventType eventType;
public:
	virtual ~ControlMusicListMenuEventInfo( ) = default;
	ControlMusicListMenuEventInfo( const EventType event_type )
		: eventType( event_type ) { }
	virtual EventType getEventType( ) const { return eventType; }
};
#endif // CONTROLMUSICLISTMENU_H_H_HEAD__FILE__
