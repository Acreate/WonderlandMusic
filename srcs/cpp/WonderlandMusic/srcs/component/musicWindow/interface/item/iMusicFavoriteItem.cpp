#include "iMusicFavoriteItem.h"

#include "iMusicItem.h"

#include "../ItemWidget/iMusicFavoriteItemWidget.h"
bool IMusicFavoriteItem::bindMusicFavoriteItem( IMusicFavoriteItemWidget *bind_target, IMusicFavoriteItem *bind_source ) {
	return bind_target->bindMusicFavoriteItem( bind_source );
}
IMusicFavoriteItem::IMusicFavoriteItem( ) {
	appendTypeInfo( this );
}
