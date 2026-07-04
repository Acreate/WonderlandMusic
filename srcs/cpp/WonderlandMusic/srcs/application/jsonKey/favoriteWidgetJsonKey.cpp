#include "favoriteWidgetJsonKey.h"

#include <QObject>

#include "../appDataManage.h"
#include "../appInstance.h"

bool FavoriteWidgetJsonKey::init( ) {
	jsonFilePath = "/app.favorte.json";
	favoriteArrayCount = "favorte.array.count";
	favoriteArrayData = "favorte.array.data";
	favoriteArrayIndex = "favorte.array.index";
	return true;
}

QString FavoriteWidgetJsonKey::getJsonFilePath( ) const {
	auto appDataManage = AppInstance::getAppInstance( )->getAppDataManage( );
	auto appSettingPath = appDataManage->getAppSettingPath( );
	return appSettingPath + jsonFilePath;
}

const QString & FavoriteWidgetJsonKey::getFavoriteArrayCount( ) const {
	return favoriteArrayCount;
}

const QString & FavoriteWidgetJsonKey::getFavoriteArrayData( ) const {
	return favoriteArrayData;
}

const QString & FavoriteWidgetJsonKey::getFavoriteArrayIndex( ) const {
	return favoriteArrayIndex;
}
