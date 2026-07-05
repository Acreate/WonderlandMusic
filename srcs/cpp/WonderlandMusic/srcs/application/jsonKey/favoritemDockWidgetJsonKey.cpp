#include "favoritemDockWidgetJsonKey.h"

bool FavoritemDockWidgetJsonKey::init( ) {
	width = "favorite.dock.width";
	return true;
}

const QString & FavoritemDockWidgetJsonKey::getWidth( ) const {
	return width;
}
