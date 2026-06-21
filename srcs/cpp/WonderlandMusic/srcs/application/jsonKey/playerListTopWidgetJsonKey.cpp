#include "playerListTopWidgetJsonKey.h"

#include "../appInstance.h"

bool PlayerListTopWidgetJsonKey::init( ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto applicationDirPath = appInstance->getAppSettingPath( );

	topJsonPath = applicationDirPath + "/program/json/app.window.player.top.info.json";
	itemWidth = "window.player.list.item.width.content.width";
	itemSplitWidth = "window.player.list.item.width.split";
	itemIndexWidth = "window.player.list.item.width.index";
	itemMusicNameWidth = "window.player.list.item.width.name";
	itemMusicSingerWidth = "window.player.list.item.width.singer";
	itemMusicDurationWidth = "window.player.list.item.width.duration";
	itemWidgetBeforeWidth = "window.player.list.item.width.before";
	itemWidgetAfterWidth = "window.player.list.item.width.after";
	return true;
}

const QString & PlayerListTopWidgetJsonKey::getTopJsonPath( ) const {
	return topJsonPath;
}

const QString & PlayerListTopWidgetJsonKey::getItemWidth( ) const {
	return itemWidth;
}

const QString & PlayerListTopWidgetJsonKey::getItemSplitWidth( ) const {
	return itemSplitWidth;
}

const QString & PlayerListTopWidgetJsonKey::getItemIndexWidth( ) const {
	return itemIndexWidth;
}

const QString & PlayerListTopWidgetJsonKey::getItemMusicNameWidth( ) const {
	return itemMusicNameWidth;
}

const QString & PlayerListTopWidgetJsonKey::getItemMusicSingerWidth( ) const {
	return itemMusicSingerWidth;
}

const QString & PlayerListTopWidgetJsonKey::getItemMusicDurationWidth( ) const {
	return itemMusicDurationWidth;
}

const QString & PlayerListTopWidgetJsonKey::getItemWidgetBeforeWidth( ) const {
	return itemWidgetBeforeWidth;
}

const QString & PlayerListTopWidgetJsonKey::getItemWidgetAfterWidth( ) const {
	return itemWidgetAfterWidth;
}
