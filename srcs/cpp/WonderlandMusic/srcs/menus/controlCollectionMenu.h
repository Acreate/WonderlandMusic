#ifndef CONTROLCOLLECTIONMENU_H_H_HEAD__FILE__
#define CONTROLCOLLECTIONMENU_H_H_HEAD__FILE__

#include <QMenu>
class ControlCollectionMenu : public QMenu {
	Q_OBJECT;
public:
	ControlCollectionMenu( ) : QMenu( ) { }
	~ControlCollectionMenu( ) override;
};
#include <macro/eventMacroDefine.h>
class Event_Default_Event_Info_Type_Name( ControlCollectionMenu ) {
public:
	enum class EventType {
		None,
		Delete_This_Menu_Ptr
	};
protected:
	EventType eventType;
public:
	virtual ~ControlCollectionMenuEventInfo( ) = default;
	ControlCollectionMenuEventInfo( const EventType event_type )
		: eventType( event_type ) { }
	virtual EventType getEventType( ) const { return eventType; }
};

#endif // CONTROLCOLLECTIONMENU_H_H_HEAD__FILE__
