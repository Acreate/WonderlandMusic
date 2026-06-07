#include "controlCollectionMenu.h"

#include "../applications/applicationEvenTrigger.h"
#include "../applications/applicationInstance.h"
ControlCollectionMenu::~ControlCollectionMenu( ) {
	auto applicationEvenTrigger = ApplicationInstance::getApplicationInstance( )->getApplicationEvenTrigger( );
	ControlCollectionMenuEvent::triggerControlCollectionMenuEvent( applicationEvenTrigger, this, ControlCollectionMenuEventInfo( ControlCollectionMenuEventInfo::EventType::Delete_This_Menu_Ptr ) );
}
