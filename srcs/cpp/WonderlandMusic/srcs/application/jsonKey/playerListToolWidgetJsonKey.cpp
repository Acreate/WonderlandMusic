#include "playerListToolWidgetJsonKey.h"

#include "../appInstance.h"

bool PlayerListToolWidgetJsonKey::init( ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto applicationDirPath = appInstance->getAppSettingPath( );

	thePreviousSongIconPath = applicationDirPath + "/program/png/上一曲.png";
	controlPlayIconPath = applicationDirPath + "/program/png/播放.png";
	controlPauseIconPath = applicationDirPath + "/program/png/暂停.png";
	theNextSongIconPath = applicationDirPath + "/program/png/下一曲.png";
	currentSongPlayListIconPath = applicationDirPath + "/program/png/列表.png";
	return true;
}

const QString & PlayerListToolWidgetJsonKey::getThePreviousSongIconPath( ) const {
	return thePreviousSongIconPath;
}

const QString & PlayerListToolWidgetJsonKey::getControlPlayIconPath( ) const {
	return controlPlayIconPath;
}

const QString & PlayerListToolWidgetJsonKey::getControlPauseIconPath( ) const {
	return controlPauseIconPath;
}

const QString & PlayerListToolWidgetJsonKey::getTheNextSongIconPath( ) const {
	return theNextSongIconPath;
}

const QString & PlayerListToolWidgetJsonKey::getCurrentSongPlayListIconPath( ) const {
	return currentSongPlayListIconPath;
}
