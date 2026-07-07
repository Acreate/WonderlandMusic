#include "appMusicManageJsonKey.h"
#include "../appDataManage.h"
#include "../appInstance.h"

bool AppMusicManageJsonKey::init( ) {
	filePath = "/json/app.music.manage.json";
	jsonObejct = "app.music.manage";
	selectFilePath = "select.file.path";
	selectDirPath = "select.dir.path";
	return true;
}

const QString & AppMusicManageJsonKey::getJsonObejct( ) const {
	return jsonObejct;
}

QString AppMusicManageJsonKey::getFilePath( ) const {
	auto appInstance = AppInstance::getAppInstance( );
	auto applicationDirPath = appInstance->getAppDataManage( )->getAppSettingPath( );
	return applicationDirPath + filePath;
}

const QString & AppMusicManageJsonKey::getSelectFilePath( ) const {
	return selectFilePath;
}

const QString & AppMusicManageJsonKey::getSelectDirPath( ) const {
	return selectDirPath;
}
