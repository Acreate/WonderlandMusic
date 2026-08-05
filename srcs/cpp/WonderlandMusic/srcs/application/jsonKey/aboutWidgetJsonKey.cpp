#include "aboutWidgetJsonKey.h"

#include "../appDataJsonKey.h"
#include "../appDataManage.h"
#include "../appInstance.h"

#include <head/defininition_get_json_key.h>

#include <tools/appJsonKeyTools.h>

Defininition_Get_Json_Key( AboutWidget );
bool AboutWidgetJsonKey::init( ) {
	qtLogoIconPath = "/png/qtlogo-64.png";
	return true;
}

QString AboutWidgetJsonKey::getQtLogoIconPath( ) const {
	auto appInstance = AppInstance::getAppInstance( );
	auto applicationDirPath = appInstance->getAppDataManage( )->getAppSettingPath( );
	return applicationDirPath + qtLogoIconPath;
}
