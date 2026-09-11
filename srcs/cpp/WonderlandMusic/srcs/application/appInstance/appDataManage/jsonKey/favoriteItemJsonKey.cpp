#include "favoriteItemJsonKey.h"
bool FavoriteItemJsonKey::init( ) {
	musicCountKey = "music.item.count";
	return true;
}
const QString & FavoriteItemJsonKey::getMusicCountKey( ) const {
	return musicCountKey;
}

const QString & FavoriteItemJsonKey::getFavoriteNameKey( ) const {
	return favoriteNameKey;
}
