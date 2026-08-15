#include "appDataManageJsonKey.h"

bool AppDataManageJsonKey::init( ) {
	filePath = "/json/app.data.manage.json";
	appMusicManageJsonObject = "app.music.manage";
	uiJsonObject = "app.music.ui";
	appSettingPath = "app.setting.path";
	return true;
}
const QString & AppDataManageJsonKey::getAppMusicManageJsonObject( ) const {
	return appMusicManageJsonObject;
}
const QString & AppDataManageJsonKey::getUiJsonObject( ) const {
	return uiJsonObject;
}
const QString & AppDataManageJsonKey::getAppSettingPath( ) const {
	return appSettingPath;
}
