#include "playerListTopWidgetJsonKey.h"

#include "../appInstance.h"

bool PlayerListTopWidgetJsonKey::init( ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto applicationDirPath = appInstance->getAppSettingPath( );

	playerListWidgetTopJsonPath = applicationDirPath + "/program/json/app.window.player.top.info.json";
	playerListWidgetItemWidth = "window.player.list.item.width.content.width";
	playerListWidgetItemSplitWidth = "window.player.list.item.width.split";
	playerListWidgetItemWidgetIndexWidth = "window.player.list.item.width.index";
	playerListWidgetItemMusicNameWidth = "window.player.list.item.width.name";
	playerListWidgetItemMusicSingerWidth = "window.player.list.item.width.singer";
	playerListWidgetItemMusicDurationWidth = "window.player.list.item.width.duration";
	playerListWidgetItemWidgetBeforeWidth = "window.player.list.item.width.before";
	playerListWidgetItemWidgetAfterWidth = "window.player.list.item.width.after";
	return true;
}

const QString & PlayerListTopWidgetJsonKey::getPlayerListWidgetTopJsonPath( ) const {
	return playerListWidgetTopJsonPath;
}

const QString & PlayerListTopWidgetJsonKey::getPlayerListWidgetItemWidth( ) const {
	return playerListWidgetItemWidth;
}

const QString & PlayerListTopWidgetJsonKey::getPlayerListWidgetItemSplitWidth( ) const {
	return playerListWidgetItemSplitWidth;
}

const QString & PlayerListTopWidgetJsonKey::getPlayerListWidgetItemWidgetIndexWidth( ) const {
	return playerListWidgetItemWidgetIndexWidth;
}

const QString & PlayerListTopWidgetJsonKey::getPlayerListWidgetItemMusicNameWidth( ) const {
	return playerListWidgetItemMusicNameWidth;
}

const QString & PlayerListTopWidgetJsonKey::getPlayerListWidgetItemMusicSingerWidth( ) const {
	return playerListWidgetItemMusicSingerWidth;
}

const QString & PlayerListTopWidgetJsonKey::getPlayerListWidgetItemMusicDurationWidth( ) const {
	return playerListWidgetItemMusicDurationWidth;
}

const QString & PlayerListTopWidgetJsonKey::getPlayerListWidgetItemWidgetBeforeWidth( ) const {
	return playerListWidgetItemWidgetBeforeWidth;
}

const QString & PlayerListTopWidgetJsonKey::getPlayerListWidgetItemWidgetAfterWidth( ) const {
	return playerListWidgetItemWidgetAfterWidth;
}
