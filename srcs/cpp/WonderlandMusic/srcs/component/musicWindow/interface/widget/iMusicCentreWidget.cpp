#include "iMusicCentreWidget.h"

#include "iMusicListWidget.h"

#include "../info/iMusicWidgetSizeInfo.h"

#include "../menu/iMusicFavoriteMenu.h"
#include "../menu/iMusicListMenu.h"

int IMusicCentreWidget::setFavoriteWidth( const int &favoriet_width ) {
	auto musicWidgetSizeInfo = getMusicWidgetSizeInfo( );
	if( musicWidgetSizeInfo == nullptr )
		return 0;
	return musicWidgetSizeInfo->setFavoriteWidth( favoriet_width );
}
int IMusicCentreWidget::setTitleHeight( const int &title_height ) {
	auto musicWidgetSizeInfo = getMusicWidgetSizeInfo( );
	if( musicWidgetSizeInfo == nullptr )
		return 0;
	return musicWidgetSizeInfo->setTitleHeight( title_height );
}
bool IMusicCentreWidget::execMenu( IMusicFavoriteWidget *music_favorite_widget, IMusicFavoriteItem *favorite_item, const QPoint &mouse_global_point ) {
	auto musicFavoriteMenu = getMusicFavoriteMenu( );
	if( musicFavoriteMenu == nullptr )
		return false;
	return musicFavoriteMenu->execMenu( music_favorite_widget, favorite_item, mouse_global_point );
}
bool IMusicCentreWidget::execMenu( IMusicListWidget *music_list_widget, IMusicItem *music_item, const QPoint &mouse_global_point ) {
	auto musicListMenu = getMusicListMenu( );
	if( musicListMenu == nullptr )
		return false;
	return musicListMenu->execMenu( music_list_widget, music_item, mouse_global_point );
}
IMusicCentreWidget::~IMusicCentreWidget( ) {
}
IMusicCentreWidget::IMusicCentreWidget( ) {
	appendTypeInfo( this );
}
