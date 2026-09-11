#include "appDataManageJsonKey.h"

bool AppDataManageJsonKey::init( ) {
	filePath = "/json/app.data.manage.json";
	uiJsonObject = "app.music.ui";
	musicItemWidthInfo = "app.music.item.size.info";
	musicWidgetSizetInfo = "app.music.widget.size.info";
	appSettingPath = "app.setting.path";
	return true;
}

const QString & AppDataManageJsonKey::getUiJsonObject( ) const {
	return uiJsonObject;
}
const QString & AppDataManageJsonKey::getAppSettingPath( ) const {
	return appSettingPath;
}
const QString & AppDataManageJsonKey::getMusicItemWidthInfo( ) const {
	return musicItemWidthInfo;
}
const QString & AppDataManageJsonKey::getMusicWidgetSizetInfo( ) const {
	return musicWidgetSizetInfo;
}
