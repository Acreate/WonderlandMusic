#include "appDataManageJsonKey.h"

#include "../../tools/pathInfoTools.h"

bool AppDataManageJsonKey::init( ) {
	jsonFilePath = "/json/app.data.manage.json";
	iniDirHomePath = "app.ini.dir.home.path";
	appMusicManage = "app.music.manage";
	return true;
}

QString AppDataManageJsonKey::getJsonFilePath( ) const {
	QString applicationDirPath;
	if( PathInfoTools::getAppSettintHomePath( applicationDirPath ) )
		return applicationDirPath + jsonFilePath;
	return jsonFilePath;
}

const QString & AppDataManageJsonKey::getAppMusicManage( ) const {
	return appMusicManage;
}

const QString & AppDataManageJsonKey::getIniDirHomePath( ) const {
	return iniDirHomePath;
}
