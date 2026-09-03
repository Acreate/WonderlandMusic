#include "iMusicFavoriteItem.h"

#include "iMusicItem.h"

#include "../ItemWidget/iMusicFavoriteItemWidget.h"
bool IMusicFavoriteItem::bindMusicFavoriteItem( IMusicFavoriteItemWidget *bind_target, IMusicFavoriteItem *bind_source ) {
	return bind_target->bindMusicFavoriteItem( bind_source );
}
bool IMusicFavoriteItem::setMusicItemFavoriteItem( IMusicItem *music_item, IMusicFavoriteItem *music_favorite_item ) {
	if( music_item == nullptr )
		return false;
	return music_item->setMusicFavoriteItem( music_favorite_item );
}
IMusicFavoriteItem::IMusicFavoriteItem( ) {
	appendTypeInfo( this );
}
