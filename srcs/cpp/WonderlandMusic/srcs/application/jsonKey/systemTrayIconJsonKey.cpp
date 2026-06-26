#include "systemTrayIconJsonKey.h"

#include "../appInstance.h"

bool SystemTrayIconJsonKey::init( ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto applicationDirPath = appInstance->getAppSettingPath( );
	iconFilePath = applicationDirPath + "/program/png/qtlogo-64.png";
	return true;
}

const QString & SystemTrayIconJsonKey::getIconFilePath( ) const {
	return iconFilePath;
}
