#include "favoriteWidgetJsonKey.h"

bool FavoriteWidgetJsonKey::init( ) {
	currentName = "favorte.active.name";
	width = "favorte.width";
	height = "favorte.height";
	return true;
}

const QString & FavoriteWidgetJsonKey::getCurrentName( ) const {
	return currentName;
}

const QString & FavoriteWidgetJsonKey::getWidth( ) const {
	return width;
}

const QString & FavoriteWidgetJsonKey::getHeight( ) const {
	return height;
}
