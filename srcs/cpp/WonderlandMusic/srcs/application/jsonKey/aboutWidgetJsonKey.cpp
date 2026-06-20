#include "aboutWidgetJsonKey.h"

#include "../appInstance.h"

bool AboutWidgetJsonKey::init( ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto applicationDirPath = appInstance->getAppSettingPath( );
	qtLogoIconPath = applicationDirPath + "/program/png/qtlogo-64.png";
	return true;
}

const QString & AboutWidgetJsonKey::getQtLogoIconPath( ) const {
	return qtLogoIconPath;
}
