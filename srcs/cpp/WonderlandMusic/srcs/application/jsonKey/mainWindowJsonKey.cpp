#include "mainWindowJsonKey.h"

#include "../appDataManage.h"
#include "../appInstance.h"

bool MainWindowJsonKey::init( ) {
	settingJsonPath = "/json/app.main.window.stting.json";
	pointXPos = "app.main.window.point.x";
	pointYPos = "app.main.window.point.y";
	sizeWidth = "app.main.window.size.w";
	sizeHeight = "app.main.window.size.h";
	return true;
}

QString MainWindowJsonKey::getSettingJsonPath( ) const {
	auto appInstance = AppInstance::getAppInstance( );
	auto applicationDirPath = appInstance->getAppDataManage( )->getAppSettingPath( );
	return applicationDirPath + settingJsonPath;
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
