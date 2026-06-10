#include "applicationEvenTrigger.h"

#include "applicationInstance.h"
ApplicationEvenTrigger::ApplicationEvenTrigger( ApplicationInstance *application ) : BaseObject( application ) {

}
ApplicationInstance * ApplicationEvenTrigger::getApplication( ) {
	return ApplicationInstance::getApplicationInstance( );
}
ApplicationEvenTrigger * ApplicationEvenTrigger::getApplicationEvenTrigger( ApplicationInstance *application ) {
	return application->getApplicationEvenTrigger( );
}
