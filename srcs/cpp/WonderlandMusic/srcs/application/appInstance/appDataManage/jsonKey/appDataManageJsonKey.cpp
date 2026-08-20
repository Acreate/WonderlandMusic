#include "appDataManageJsonKey.h"

bool AppDataManageJsonKey::init( ) {
	filePath = "/json/app.data.manage.json";
	uiJsonObject = "app.music.ui";
	appSettingPath = "app.setting.path";
	return true;
}

const QString & AppDataManageJsonKey::getUiJsonObject( ) const {
	return uiJsonObject;
}
const QString & AppDataManageJsonKey::getAppSettingPath( ) const {
	return appSettingPath;
}
