#include "playerListJsonKey.h"

#include "../appInstance.h"

bool PlayerListJsonKey::init( ) {
	auto appInstance = AppInstance::getAppInstance( );
	auto applicationDirPath = appInstance->getAppSettingPath( );

	songPlayerInfoJsonPath = applicationDirPath + "/program/json/app.song.play.list.info.json";
	musicPlayerListInfoFileJsonPath = applicationDirPath + "/program/json/app.player.list.widget.music.list.info.json";
	musicInfoListCount = "list.size";
	musicInfoListName = "list.name";
	musicInfoListIndex = "list.index";
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
