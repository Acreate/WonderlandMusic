#include "favoriteSrollAreaJsonKey.h"

bool FavoriteSrollAreaJsonKey::init( ) {
	objectName = "favorite.srollArea";
	width = "width";
	width = "height";
	return true;
}

const QString & FavoriteSrollAreaJsonKey::getWidth( ) const {
	return width;
}

const QString & FavoriteSrollAreaJsonKey::getObjectName( ) const {
	return objectName;
}

const QString & FavoriteSrollAreaJsonKey::getHeight( ) const {
	return height;
}
