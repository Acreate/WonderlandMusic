#include "iMusicItem.h"

#include "../ItemWidget/iMusicItemWidget.h"

IMusicItem::~IMusicItem( ) {
}
IMusicItem::IMusicItem( ) {
	appendTypeInfo( this );
}
