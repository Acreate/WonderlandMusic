#include "musicWidgetSizeInfoJsonKey.h"
bool MusicWidgetSizeInfoJsonKey::init( ) {
	favoriteWidth = QObject::tr( "favorite.width" );
	titleHeight = QObject::tr( "title.height" );
	return true;
}
const QString & MusicWidgetSizeInfoJsonKey::getFavoriteWidth( ) const {
	return favoriteWidth;
}
const QString & MusicWidgetSizeInfoJsonKey::getTitleHeight( ) const {
	return titleHeight;
}
