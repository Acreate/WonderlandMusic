#include "controlMusicListMenu.h"

#include <source_location>

#include "../applications/applicationEvenTrigger.h"
#include "../applications/applicationInstance.h"
ControlMusicListMenu::ControlMusicListMenu( QWidget *const parent ) : BaseMenu( parent ) {

}
ControlMusicListMenu::ControlMusicListMenu( const QString &titile, QWidget *const parent ) : BaseMenu( titile, parent ) {
}
ControlMusicListMenu::ControlMusicListMenu( const QString &titile ) : BaseMenu( titile ) {

}
ControlMusicListMenu::ControlMusicListMenu( ) {

}
ControlMusicListMenu::~ControlMusicListMenu( ) {
	auto applicationInstance = ApplicationInstance::getApplicationInstance( );
	auto applicationEvenTrigger = applicationInstance->getApplicationEvenTrigger( );
	ControlMusicListMenuEvent::triggerControlMusicListMenuEvent( applicationEvenTrigger, this, ControlMusicListMenuEventInfo( ControlMusicListMenuEventInfo::EventType::Delete_This_Menu_Ptr ) );
}
