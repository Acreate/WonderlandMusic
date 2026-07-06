#include "favoritemDockWidgetJsonKey.h"

bool FavoritemDockWidgetJsonKey::init( ) {
	objectName = "favoritem.dock.widget";
	width = "width";
	return true;
}

const QString & FavoritemDockWidgetJsonKey::getObjectName( ) const {
	return objectName;
}

const QString & FavoritemDockWidgetJsonKey::getWidth( ) const {
	return width;
}
