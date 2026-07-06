#include "favoritemDockWidgetJsonKey.h"

bool FavoritemDockWidgetJsonKey::init( ) {
	objectName = "favoritem.dock.widget";
	width = "width";
	height = "height";
	return true;
}

const QString & FavoritemDockWidgetJsonKey::getObjectName( ) const {
	return objectName;
}

const QString & FavoritemDockWidgetJsonKey::getWidth( ) const {
	return width;
}

const QString & FavoritemDockWidgetJsonKey::getHeight( ) const {
	return height;
}
