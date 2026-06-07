#include "controlMusicListMenu.h"
#include "../applications/applicationEvenTrigger.h"
#include "../applications/applicationInstance.h"
ControlMusicListMenu::~ControlMusicListMenu( ) {
	auto applicationEvenTrigger = ApplicationInstance::getApplicationInstance( )->getApplicationEvenTrigger( );
	ControlMusicListMenuEvent::triggerControlMusicListMenuEvent( applicationEvenTrigger, this, ControlMusicListMenuEventInfo( ControlMusicListMenuEventInfo::EventType::Delete_This_Menu_Ptr ) );
}
