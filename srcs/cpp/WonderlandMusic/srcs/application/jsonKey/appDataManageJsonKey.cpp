#include "appDataManageJsonKey.h"

#include "../appDataManage.h"
#include "../appInstance.h"

bool AppDataManageJsonKey::init( ) {
	jsonFilePath = "/json/app.data.manage.json";
	iniDirHomePath = "app.ini.dir.home.path";
	appMusicManage = "app.music.manage";
	return true;
}

QString AppDataManageJsonKey::getJsonFilePath( ) const {
	auto appInstance = AppInstance::getAppInstance( );
	auto applicationDirPath = appInstance->getAppDataManage( )->getAppSettingPath( );
	return applicationDirPath + jsonFilePath;
}

const QString & AppDataManageJsonKey::getAppMusicManage( ) const {
	return appMusicManage;
}

const QString & AppDataManageJsonKey::getIniDirHomePath( ) const {
	return iniDirHomePath;
}
