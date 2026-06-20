#include "playerWindowJsonKey.h"

#include "../appInstance.h"

bool PlayerWindowJsonKey::init( ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto applicationDirPath = appInstance->getAppSettingPath( );

	playerWindowSettingJsonPath = applicationDirPath + "/program/json/app.window.player.work.select.info.json";
	playerWindowFileSelectWorkPath = "window.player.path.file.select";
	playerWindowDirSelectWorkPath = "window.player.path.dir.select";
	return true;
}

const QString & PlayerWindowJsonKey::getPlayerWindowSettingJsonPath( ) const {
	return playerWindowSettingJsonPath;
}

const QString & PlayerWindowJsonKey::getPlayerWindowFileSelectWorkPath( ) const {
	return playerWindowFileSelectWorkPath;
}

const QString & PlayerWindowJsonKey::getPlayerWindowDirSelectWorkPath( ) const {
	return playerWindowDirSelectWorkPath;
}
