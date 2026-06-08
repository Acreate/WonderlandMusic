#include "controlCollectionMenu.h"

#include <source_location>

#include "../applications/applicationEvenTrigger.h"
#include "../applications/applicationInstance.h"
ControlCollectionMenu::ControlCollectionMenu( QWidget *parent ) : BaseMenu( parent ) {

}
ControlCollectionMenu::ControlCollectionMenu( const QString &titile, QWidget *parent ) : BaseMenu( titile, parent ) {

}
ControlCollectionMenu::ControlCollectionMenu( const QString &titile ) : BaseMenu( titile ) {

}
ControlCollectionMenu::ControlCollectionMenu( ) {

}
ControlCollectionMenu::~ControlCollectionMenu( ) {

	auto applicationInstance = ApplicationInstance::getApplicationInstance( );
	auto applicationEvenTrigger = applicationInstance->getApplicationEvenTrigger( );
	ControlCollectionMenuEvent::triggerControlCollectionMenuEvent( applicationEvenTrigger, this, ControlCollectionMenuEventInfo( ControlCollectionMenuEventInfo::EventType::Delete_This_Menu_Ptr ) );
}
