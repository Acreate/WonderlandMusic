#include "favoriteWidgetTranslate.h"

bool FavoriteWidgetTranslate::init( ) {
	defautFavoriteName = QObject::tr( "默认" );
	return true;
}

const QString & FavoriteWidgetTranslate::getDefautFavoriteName( ) const {
	return defautFavoriteName;
}
