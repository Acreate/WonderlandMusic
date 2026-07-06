#include "favoriteWidgetJsonKey.h"

bool FavoriteWidgetJsonKey::init( ) {
	objectName = "favorite.widget";
	width = "width";
	height = "height";
	return true;
}

const QString & FavoriteWidgetJsonKey::getObjectName( ) const {
	return objectName;
}

const QString & FavoriteWidgetJsonKey::getWidth( ) const {
	return width;
}

const QString & FavoriteWidgetJsonKey::getHeight( ) const {
	return height;
}
