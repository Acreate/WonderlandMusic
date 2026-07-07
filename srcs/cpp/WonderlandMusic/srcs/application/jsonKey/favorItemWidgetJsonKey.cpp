#include "favorItemWidgetJsonKey.h"

const QString & FavorItemWidgetJsonKey::getFavoriteVector( ) const {
	return favoriteVector;
}

const QString & FavorItemWidgetJsonKey::getFavoriteData( ) const {
	return favoriteData;
}

const QString & FavorItemWidgetJsonKey::getFavoriteCount( ) const {
	return favoriteCount;
}

const QString & FavorItemWidgetJsonKey::getFavorItemWidget( ) const {
	return favorItemWidget;
}

const QString & FavorItemWidgetJsonKey::getName( ) const {
	return name;
}

bool FavorItemWidgetJsonKey::init( ) {
	favorItemWidget = "favorite";
	favorItemWidget = "name";
	favoriteVector = "favorite.vector";
	favoriteData = "favorite.data";
	favoriteCount = "favorite.count";
	return true;
}
