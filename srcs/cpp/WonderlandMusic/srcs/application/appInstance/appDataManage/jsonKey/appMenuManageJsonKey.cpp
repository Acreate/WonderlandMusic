#include "appMenuManageJsonKey.h"
bool AppMenuManageJsonKey::init( ) {
	musicFavoriteMenuJsonObjectKey = "menu.music.favorite.json";
	musicListMenuJsonObjectKey = "menu.music.list.json";
	return true;
}
const QString & AppMenuManageJsonKey::getMusicFavoriteMenuJsonObjectKey( ) const {
	return musicFavoriteMenuJsonObjectKey;
}
const QString & AppMenuManageJsonKey::getMusicListMenuJsonObjectKey( ) const {
	return musicListMenuJsonObjectKey;
}
