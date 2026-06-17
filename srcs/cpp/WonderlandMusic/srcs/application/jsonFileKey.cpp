#include "jsonFileKey.h"

#include "appInstance.h"
JsonFileKey::JsonFileKey( ) { }
bool JsonFileKey::init( ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto applicationDirPath = appInstance->applicationDirPath( );

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

	return true;
}
