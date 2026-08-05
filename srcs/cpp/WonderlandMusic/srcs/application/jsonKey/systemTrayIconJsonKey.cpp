#include "systemTrayIconJsonKey.h"

#include "../appDataManage.h"
#include "../appInstance.h"

#include <head/defininition_get_json_key.h>

#include <tools/instanceTools.h>
#include "../appDataJsonKey.h"

Defininition_Get_Json_Key (SystemTrayIcon);
bool SystemTrayIconJsonKey::init( ) {
	iconFilePath = "/png/qtlogo-64.png";
	return true;
}

QString SystemTrayIconJsonKey::getIconFilePath( ) const {
	auto appInstance = AppInstance::getAppInstance( );
	auto applicationDirPath = appInstance->getAppDataManage( )->getAppSettingPath( );
	return applicationDirPath + iconFilePath;
}
