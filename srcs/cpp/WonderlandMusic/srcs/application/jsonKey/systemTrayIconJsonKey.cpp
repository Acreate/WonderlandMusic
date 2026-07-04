#include "systemTrayIconJsonKey.h"

#include "../appDataManage.h"
#include "../appInstance.h"

bool SystemTrayIconJsonKey::init( ) {
	iconFilePath = "/png/qtlogo-64.png";
	return true;
}

QString SystemTrayIconJsonKey::getIconFilePath( ) const {
	auto appInstance = AppInstance::getAppInstance( );
	auto applicationDirPath = appInstance->getAppDataManage( )->getAppSettingPath( );
	return applicationDirPath + iconFilePath;
}
