#include "appDataManageJsonKey.h"

#include "../appDataManage.h"
#include "../appInstance.h"

bool AppDataManageJsonKey::init( ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto applicationDirPath = appInstance->getAppDataManage( )->getAppSettingPath( );
	jsonFilePath = applicationDirPath + "/json/app.data.manage.json";
	iniDirHomePath = "app.ini.dir.home.path";
	appMusicManage = "app.music.manage";
	return true;
}

const QString & AppDataManageJsonKey::getJsonFilePath( ) const {
	return jsonFilePath;
}

const QString & AppDataManageJsonKey::getAppMusicManage( ) const {
	return appMusicManage;
}

const QString & AppDataManageJsonKey::getIniDirHomePath( ) const {
	return iniDirHomePath;
}
