#include "playerListToolWidgetJsonKey.h"

#include "../appDataManage.h"
#include "../appInstance.h"

bool PlayerListToolWidgetJsonKey::init( ) {
	thePreviousSongIconPath = "/png/上一曲.png";
	controlPlayIconPath = "/png/播放.png";
	controlPauseIconPath = "/png/暂停.png";
	theNextSongIconPath = "/png/下一曲.png";
	currentSongPlayListIconPath = "/png/列表.png";
	return true;
}

QString PlayerListToolWidgetJsonKey::getThePreviousSongIconPath( ) const {
	auto appInstance = AppInstance::getAppInstance( );
	auto applicationDirPath = appInstance->getAppDataManage( )->getAppSettingPath( );
	return applicationDirPath + thePreviousSongIconPath;
}

QString PlayerListToolWidgetJsonKey::getControlPlayIconPath( ) const {
	auto appInstance = AppInstance::getAppInstance( );
	auto applicationDirPath = appInstance->getAppDataManage( )->getAppSettingPath( );
	return applicationDirPath + controlPlayIconPath;
}

QString PlayerListToolWidgetJsonKey::getControlPauseIconPath( ) const {
	auto appInstance = AppInstance::getAppInstance( );
	auto applicationDirPath = appInstance->getAppDataManage( )->getAppSettingPath( );
	return applicationDirPath + controlPauseIconPath;
}

QString PlayerListToolWidgetJsonKey::getTheNextSongIconPath( ) const {
	auto appInstance = AppInstance::getAppInstance( );
	auto applicationDirPath = appInstance->getAppDataManage( )->getAppSettingPath( );
	return applicationDirPath + theNextSongIconPath;
}

QString PlayerListToolWidgetJsonKey::getCurrentSongPlayListIconPath( ) const {
	auto appInstance = AppInstance::getAppInstance( );
	auto applicationDirPath = appInstance->getAppDataManage( )->getAppSettingPath( );
	return applicationDirPath + currentSongPlayListIconPath;
}
