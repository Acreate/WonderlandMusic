#include "favoriteItemJsonKey.h"

bool FavoriteItemJsonKey::init( ) {
	favoriteItemArrayObject = "favorite.item.array.object";
	favoriteItemArray = "favorite.item.array";
	favoriteItemCount = "favorite.item.cout";
	favoriteName = "favorite.name";
	musicCount = "music.count";
	musicArray = "music.array";
	return true;
}

const QString & FavoriteItemJsonKey::getFavoriteItemArray( ) const {
	return favoriteItemArray;
}

const QString & FavoriteItemJsonKey::getFavoriteItemCount( ) const {
	return favoriteItemCount;
}

const QString & FavoriteItemJsonKey::getFavoriteName( ) const {
	return favoriteName;
}

const QString & FavoriteItemJsonKey::getMusicCount( ) const {
	return musicCount;
}

const QString & FavoriteItemJsonKey::getMusicArray( ) const {
	return musicArray;
}

const QString & FavoriteItemJsonKey::getFavoriteItemArrayObject( ) const {
	return favoriteItemArrayObject;
}
