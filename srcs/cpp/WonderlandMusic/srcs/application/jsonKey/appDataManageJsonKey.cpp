#include "appDataManageJsonKey.h"

bool AppDataManageJsonKey::init( ) {
	filePath = "/json/app.data.manage.json";
	iniDirHomePath = "app.ini.dir.home.path";
	appMusicManage = "app.music.manage";
	return true;
}

const QString & AppDataManageJsonKey::getAppMusicManage( ) const {
	return appMusicManage;
}

const QString & AppDataManageJsonKey::getIniDirHomePath( ) const {
	return iniDirHomePath;
}
