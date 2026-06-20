#include "mainWindowJsonKey.h"

#include "../appInstance.h"

bool MainWindowJsonKey::init( ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto applicationDirPath = appInstance->getAppSettingPath( );

	mainWindowSettingJsonPath = applicationDirPath + "/program/json/app.main.window.stting.json";
	mainWindowPointXPos = "app.main.window.point.x";
	mainWindowPointYPos = "app.main.window.point.y";
	mainWindowSizeWidth = "app.main.window.size.w";
	mainWindowSizeHeight = "app.main.window.size.h";
	return true;
}

const QString & MainWindowJsonKey::getMainWindowSettingJsonPath( ) const {
	return mainWindowSettingJsonPath;
}

const QString & MainWindowJsonKey::getMainWindowPointXPos( ) const {
	return mainWindowPointXPos;
}

const QString & MainWindowJsonKey::getMainWindowPointYPos( ) const {
	return mainWindowPointYPos;
}

const QString & MainWindowJsonKey::getMainWindowSizeWidth( ) const {
	return mainWindowSizeWidth;
}

const QString & MainWindowJsonKey::getMainWindowSizeHeight( ) const {
	return mainWindowSizeHeight;
}
