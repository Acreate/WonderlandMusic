#include "jsonFileKey.h"

#include "appInstance.h"

JsonFileKey::JsonFileKey( ) {
}

bool JsonFileKey::init( ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto applicationDirPath = appInstance->getAppSettingPath( );

	mainWindowSettingJsonPath = applicationDirPath + "/program/json/app.main.window.stting.json";
	mainWindowPointXPos = "app.main.window.point.x";
	mainWindowPointYPos = "app.main.window.point.y";
	mainWindowSizeWidth = "app.main.window.size.w";
	mainWindowSizeHeight = "app.main.window.size.h";

	musicPlayerListInfoFileJsonPath = applicationDirPath + "/program/json/app.player.list.widget.music.list.info.json";
	musicInfoListCount = "list.size";
	musicInfoListName = "list.name";
	musicInfoListIndex = "list.index";
	musicInfoFile = "file.name";
	musicInfoName = "music.name";
	musicInfoSinger = "music.singer";
	musicInfoDuration = "music.duartion";

	playerWindowSettingJsonPath = applicationDirPath + "/program/json/app.window.player.work.select.info.json";
	playerWindowFileSelectWorkPath = "window.player.path.file.select";
	playerWindowDirSelectWorkPath = "window.player.path.dir.select";

	playerListWidgetTopJsonPath = applicationDirPath + "/program/json/app.window.player.top.info.json";
	playerListWidgetItemSplitWidth = "window.player.list.item.width.split";
	playerListWidgetItemWidgetIndexWidth = "window.player.list.item.width.index";
	playerListWidgetItemMusicNameWidth = "window.player.list.item.width.name";
	playerListWidgetItemMusicSingerWidth = "window.player.list.item.width.singer";
	playerListWidgetItemMusicDurationWidth = "window.player.list.item.width.duration";
	playerListWidgetItemWidgetBeforeWidth = "window.player.list.item.width.before";
	playerListWidgetItemWidgetAfterWidth = "window.player.list.item.width.after";
	return true;
}

const QString & JsonFileKey::getMainWindowSettingJsonPath( ) const {
	return mainWindowSettingJsonPath;
}

const QString & JsonFileKey::getMainWindowPointXPos( ) const {
	return mainWindowPointXPos;
}

const QString & JsonFileKey::getMainWindowPointYPos( ) const {
	return mainWindowPointYPos;
}

const QString & JsonFileKey::getMainWindowSizeWidth( ) const {
	return mainWindowSizeWidth;
}

const QString & JsonFileKey::getMainWindowSizeHeight( ) const {
	return mainWindowSizeHeight;
}

const QString & JsonFileKey::getMusicPlayerListInfoFileJsonPath( ) const {
	return musicPlayerListInfoFileJsonPath;
}

const QString & JsonFileKey::getMusicInfoFile( ) const {
	return musicInfoFile;
}

const QString & JsonFileKey::getMusicInfoName( ) const {
	return musicInfoName;
}

const QString & JsonFileKey::getMusicInfoSinger( ) const {
	return musicInfoSinger;
}

const QString & JsonFileKey::getMusicInfoDuration( ) const {
	return musicInfoDuration;
}

const QString & JsonFileKey::getMusicInfoListCount( ) const {
	return musicInfoListCount;
}

const QString & JsonFileKey::getMusicInfoListName( ) const {
	return musicInfoListName;
}

const QString & JsonFileKey::getMusicInfoListIndex( ) const {
	return musicInfoListIndex;
}

const QString & JsonFileKey::getPlayerWindowSettingJsonPath( ) const {
	return playerWindowSettingJsonPath;
}

const QString & JsonFileKey::getPlayerWindowFileSelectWorkPath( ) const {
	return playerWindowFileSelectWorkPath;
}

const QString & JsonFileKey::getPlayerWindowDirSelectWorkPath( ) const {
	return playerWindowDirSelectWorkPath;
}

const QString & JsonFileKey::getPlayerListWidgetItemSplitWidth( ) const {
	return playerListWidgetItemSplitWidth;
}

const QString & JsonFileKey::getPlayerListWidgetItemWidgetIndexWidth( ) const {
	return playerListWidgetItemWidgetIndexWidth;
}

const QString & JsonFileKey::getPlayerListWidgetItemMusicNameWidth( ) const {
	return playerListWidgetItemMusicNameWidth;
}

const QString & JsonFileKey::getPlayerListWidgetItemMusicSingerWidth( ) const {
	return playerListWidgetItemMusicSingerWidth;
}

const QString & JsonFileKey::getPlayerListWidgetItemMusicDurationWidth( ) const {
	return playerListWidgetItemMusicDurationWidth;
}

const QString & JsonFileKey::getPlayerListWidgetTopJsonPath( ) const {
	return playerListWidgetTopJsonPath;
}

const QString & JsonFileKey::getPlayerListWidgetItemWidgetBeforeWidth( ) const {
	return playerListWidgetItemWidgetBeforeWidth;
}

const QString & JsonFileKey::getPlayerListWidgetItemWidgetAfterWidth( ) const {
	return playerListWidgetItemWidgetAfterWidth;
}
