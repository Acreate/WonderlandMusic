#include "systemTrayIconJsonKey.h"

#include "../appDataManage.h"
#include "../appInstance.h"

bool SystemTrayIconJsonKey::init( ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto applicationDirPath = appInstance->getAppDataManage( )->getAppSettingPath( );
	iconFilePath = applicationDirPath + "/png/qtlogo-64.png";
	return true;
}

const QString & SystemTrayIconJsonKey::getIconFilePath( ) const {
	return iconFilePath;
}
