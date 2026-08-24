#include "iMusicItem.h"

#include "../ItemWidget/iMusicItemWidget.h"
IMusicItem::IMusicItem( ) {
	appendTypeInfo( this );
}
bool IMusicItem::setMusicItemWidgetMusicCentreWidget( ) {
	auto musicItemWidget = getMusicItemWidget( );
	if( musicItemWidget == nullptr )
		return false;
	auto musicCentreWidget = getMusicCentreWidget( );
	return musicItemWidget->setMusicCentreWidget( musicCentreWidget );
}
bool IMusicItem::setMusicItemWidgetBindMusicItem( ) {
	auto musicItemWidget = getMusicItemWidget( );
	if( musicItemWidget == nullptr )
		return false;
	return musicItemWidget->setBindMusicItem( this );
}
