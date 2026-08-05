#include "appUserInterfaceManageJsonKey.h"

#include "../appDataManage.h"
#include "../appInstance.h"

#include <head/defininition_get_json_key.h>

#include <tools/instanceTools.h>
#include "../appDataJsonKey.h"
Defininition_Get_Json_Key( AppUserInterfaceManage );

bool AppUserInterfaceManageJsonKey::init( ) {
	filePath = "/json/app.ui.json";
	mainWindow = "main.window.info";
	musicListTopWidget = "music.window.list.top.info";
	musicFavoriteWidget = "music.window.favorite.info";
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

const QString & AppUserInterfaceManageJsonKey::getMusicListTopWidget( ) const {
	return musicListTopWidget;
}

const QString & AppUserInterfaceManageJsonKey::getMusicFavoriteWidget( ) const {
	return musicFavoriteWidget;
}
