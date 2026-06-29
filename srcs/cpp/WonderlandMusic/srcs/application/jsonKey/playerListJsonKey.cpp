#include "playerListJsonKey.h"

#include "../appDataManage.h"
#include "../appInstance.h"

bool PlayerListJsonKey::init( ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto applicationDirPath = appInstance->getAppDataManage( )->getAppSettingPath( );
	songPlayerInfoJsonPath = applicationDirPath + "/json/app.song.play.list.info.json";
	musicPlayerListInfoFileJsonPath = applicationDirPath + "/json/app.player.list.widget.music.list.info.json";
	musicInfoListCount = "list.size";
	musicInfoListName = "list.name";
	musicInfoListIndex = "list.index";
	fileSelectWorkPath = "play.window.menu.player.path.file.select";
	dirSelectWorkPath = "play.window.menu.player.path.dir.select";
	return true;
}

const QString & PlayerListJsonKey::getMusicPlayerListInfoFileJsonPath( ) const {
	return musicPlayerListInfoFileJsonPath;
}

const QString & PlayerListJsonKey::getMusicInfoListCount( ) const {
	return musicInfoListCount;
}

const QString & PlayerListJsonKey::getMusicInfoListName( ) const {
	return musicInfoListName;
}

const QString & PlayerListJsonKey::getMusicInfoListIndex( ) const {
	return musicInfoListIndex;
}

const QString & PlayerListJsonKey::getSongPlayerInfoJsonPath( ) const {
	return songPlayerInfoJsonPath;
}

const QString & PlayerListJsonKey::getFileSelectWorkPath( ) const {
	return fileSelectWorkPath;
}

const QString & PlayerListJsonKey::getDirSelectWorkPath( ) const {
	return dirSelectWorkPath;
}
