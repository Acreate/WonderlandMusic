#include "playerWindowJsonKey.h"

#include "../appDataManage.h"
#include "../appInstance.h"

bool PlayerWindowJsonKey::init( ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto applicationDirPath = appInstance->getAppDataManage( )->getAppSettingPath( );
	jsonFilePath = applicationDirPath + "/json/app.window.player.window.info.json";

	fileSelect = "file.select.path";
	dirSelect = "dir.select.path";

	favoriteArrayObjName = "favorite.array";
	favoriteArrayCount = "favorite.count";
	favoriteArrayData = "favorite.data";
	favoriteName = "favorite.name";
	favoriteCodeArray = "favorite.code.array";

	musicArrayObjName = "music.array";
	musicArrayCount = "music.count";
	musicArrayData = "music.data";
	return true;
}

const QString & PlayerWindowJsonKey::getJsonFilePath( ) const {
	return jsonFilePath;
}

const QString & PlayerWindowJsonKey::getFavoriteArrayObjName( ) const {
	return favoriteArrayObjName;
}

const QString & PlayerWindowJsonKey::getFavoriteArrayCount( ) const {
	return favoriteArrayCount;
}

const QString & PlayerWindowJsonKey::getFavoriteArrayData( ) const {
	return favoriteArrayData;
}

const QString & PlayerWindowJsonKey::getFileSelect( ) const {
	return fileSelect;
}

const QString & PlayerWindowJsonKey::getDirSelect( ) const {
	return dirSelect;
}

const QString & PlayerWindowJsonKey::getMusicArrayObjName( ) const {
	return musicArrayObjName;
}

const QString & PlayerWindowJsonKey::getMusicArrayCount( ) const {
	return musicArrayCount;
}

const QString & PlayerWindowJsonKey::getMusicArrayData( ) const {
	return musicArrayData;
}

const QString & PlayerWindowJsonKey::getFavoriteName( ) const {
	return favoriteName;
}

const QString & PlayerWindowJsonKey::getFavoriteCodeArray( ) const {
	return favoriteCodeArray;
}
