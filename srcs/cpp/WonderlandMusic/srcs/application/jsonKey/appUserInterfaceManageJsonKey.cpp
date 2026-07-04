#include "appUserInterfaceManageJsonKey.h"

#include "../appDataManage.h"
#include "../appInstance.h"

bool AppUserInterfaceManageJsonKey::init( ) {
	filePath = "/json/app.ui.json";
	mainWindow = "main.window.info";
	musicListTopDockWidget = "music.window.list.top.info";
	return true;
}

const QString & AppUserInterfaceManageJsonKey::getMainWindow( ) const {
	return mainWindow;
}

QString AppUserInterfaceManageJsonKey::getFilePath( ) const {
	auto appInstance = AppInstance::getAppInstance( );
	auto applicationDirPath = appInstance->getAppDataManage( )->getAppSettingPath( );
	return applicationDirPath + filePath;
}

const QString & AppUserInterfaceManageJsonKey::getMusicListTopDockWidget( ) const {
	return musicListTopDockWidget;
}
