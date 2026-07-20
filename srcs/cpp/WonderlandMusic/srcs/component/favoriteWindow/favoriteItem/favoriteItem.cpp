#include "favoriteItem.h"
#include "../favoriteWindow.h"

FavoriteItem::~FavoriteItem( ) {
	favoriteWindow->deleteItemInfo( this );
}

FavoriteItem::FavoriteItem( FavoriteWindow *favorite_window, const QString &name ) : favoriteWindow( favorite_window ), name( name ) {
	favoriteWindow->updateItemInfo( this );
}

const QString & FavoriteItem::getName( ) const {
	return name;
}

void FavoriteItem::setName( const QString &name ) {
	this->name = name;
	favoriteWindow->updateItemInfo( this );
}
