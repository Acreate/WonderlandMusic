#include "iMusicItem.h"

#include "../ItemWidget/iMusicItemWidget.h"
bool IMusicItem::binMusicItemWidget( IMusicItemWidget *bind_target, IMusicItem *bind_source ) {
	return bind_target->bindMusicItem( bind_source );
}
IMusicItem::IMusicItem( ) {
	appendTypeInfo( this );
}
