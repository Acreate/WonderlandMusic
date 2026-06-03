#include "applicationInstance.h"
ApplicationInstance *ApplicationInstance::instance = nullptr;
ApplicationInstance::ApplicationInstance( Application *const application ) : application( application ) { }
ApplicationInstance * ApplicationInstance::getInstance( ) {
	return instance;
}
