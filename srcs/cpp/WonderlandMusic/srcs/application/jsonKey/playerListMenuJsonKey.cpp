#include "playerListMenuJsonKey.h"

#include "../appDataManage.h"
#include "../appInstance.h"

bool PlayerListMenuJsonKey::init( ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto applicationDirPath = appInstance->getAppDataManage( )->getAppSettingPath( );
	settingJsonPath = applicationDirPath + "/json/app.player.work.select.info.json";
	return true;
}

const QString & PlayerListMenuJsonKey::getSettingJsonPath( ) const {
	return settingJsonPath;
}
