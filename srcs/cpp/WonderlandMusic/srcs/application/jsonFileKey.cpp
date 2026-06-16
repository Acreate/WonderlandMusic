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
	musicInfoFile = "file.name";
	musicInfoName = "music.name";
	musicInfoSinger = "music.singer";
	musicInfoDuration = "music.duartion";

	return true;
}
