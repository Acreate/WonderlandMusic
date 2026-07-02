#include "aboutWidgetJsonKey.h"

#include "../appDataManage.h"
#include "../appInstance.h"

bool AboutWidgetJsonKey::init( ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto applicationDirPath = appInstance->getAppDataManage( )->getAppSettingPath( );
	qtLogoIconPath = applicationDirPath + "/png/qtlogo-64.png";
	return true;
}

const QString & AboutWidgetJsonKey::getQtLogoIconPath( ) const {
	return qtLogoIconPath;
}
