#include "playerListMenuJsonKey.h"

#include "../appInstance.h"

bool PlayerListMenuJsonKey::init( ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto applicationDirPath = appInstance->getAppSettingPath( );
	settingJsonPath = applicationDirPath + "/json/app.player.work.select.info.json";
	fileSelectWorkPath = "play.window.menu.player.path.file.select";
	dirSelectWorkPath = "play.window.menu.player.path.dir.select";
	return true;
}

const QString & PlayerListMenuJsonKey::getSettingJsonPath( ) const {
	return settingJsonPath;
}

const QString & PlayerListMenuJsonKey::getFileSelectWorkPath( ) const {
	return fileSelectWorkPath;
}

const QString & PlayerListMenuJsonKey::getDirSelectWorkPath( ) const {
	return dirSelectWorkPath;
}
