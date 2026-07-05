#include "favoriteWidgetMenuTranslate.h"

bool FavoriteWidgetMenuTranslate::init( ) {
	addFavorite = QObject::tr( "添加收藏夹" );
	deleteFavorite = QObject::tr( "删除收藏夹" );
	changeFavorite = QObject::tr( "更改收藏夹" );
	return true;
}

const QString & FavoriteWidgetMenuTranslate::getAddFavorite( ) const {
	return addFavorite;
}

const QString & FavoriteWidgetMenuTranslate::getDeleteFavorite( ) const {
	return deleteFavorite;
}

const QString & FavoriteWidgetMenuTranslate::getChangeFavorite( ) const {
	return changeFavorite;
}
