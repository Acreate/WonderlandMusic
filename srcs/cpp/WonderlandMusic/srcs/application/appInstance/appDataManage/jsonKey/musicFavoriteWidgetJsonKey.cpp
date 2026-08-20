#include "musicFavoriteWidgetJsonKey.h"
bool MusicFavoriteWidgetJsonKey::init( ) {
	countKey = "favorite.count";
	favoriteVectorKey = "favorite.vector";
	return true;
}
const QString & MusicFavoriteWidgetJsonKey::getCountKey( ) const {
	return countKey;
}
const QString & MusicFavoriteWidgetJsonKey::getFavoriteVectorKey( ) const {
	return favoriteVectorKey;
}
