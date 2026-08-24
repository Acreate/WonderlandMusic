#include "iMusicItem.h"

#include "../ItemWidget/iMusicItemWidget.h"
IMusicItem::IMusicItem( ) {
	appendTypeInfo( this );
}
bool IMusicItem::setMusicItemWidgetMusicCentreWidget( MusicCentreWidget *music_centre_widget ) {
	auto musicItemWidget = getMusicItemWidget( );
	if( musicItemWidget == nullptr )
		return false;
	return musicItemWidget->setMusicCentreWidget( music_centre_widget );
}
