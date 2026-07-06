#include "favoriteSrollAreaJsonKey.h"

bool FavoriteSrollAreaJsonKey::init( ) {
	width = "Favorite.SrollArea.widget.width";
	return true;
}

const QString & FavoriteSrollAreaJsonKey::getWidth( ) const {
	return width;
}
