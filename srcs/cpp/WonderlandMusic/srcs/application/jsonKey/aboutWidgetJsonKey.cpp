#include "aboutWidgetJsonKey.h"

#include "../appDataManage.h"
#include "../appInstance.h"

bool AboutWidgetJsonKey::init( ) {
	qtLogoIconPath = "/png/qtlogo-64.png";
	return true;
}

QString AboutWidgetJsonKey::getQtLogoIconPath( ) const {
	auto appInstance = AppInstance::getAppInstance( );
	auto applicationDirPath = appInstance->getAppDataManage( )->getAppSettingPath( );
	return applicationDirPath + qtLogoIconPath;
}
