#include "mainWindowJsonKey.h"

#include "../appDataManage.h"
#include "../appInstance.h"

bool MainWindowJsonKey::init( ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto applicationDirPath = appInstance->getAppDataManage( )->getAppSettingPath( );
	settingJsonPath = applicationDirPath + "/json/app.main.window.stting.json";
	pointXPos = "app.main.window.point.x";
	pointYPos = "app.main.window.point.y";
	sizeWidth = "app.main.window.size.w";
	sizeHeight = "app.main.window.size.h";
	return true;
}


const QString & MainWindowJsonKey::getSettingJsonPath( ) const {
	return settingJsonPath;
}

const QString & MainWindowJsonKey::getPointXPos( ) const {
	return pointXPos;
}

const QString & MainWindowJsonKey::getPointYPos( ) const {
	return pointYPos;
}

const QString & MainWindowJsonKey::getSizeWidth( ) const {
	return sizeWidth;
}

const QString & MainWindowJsonKey::getSizeHeight( ) const {
	return sizeHeight;
}
