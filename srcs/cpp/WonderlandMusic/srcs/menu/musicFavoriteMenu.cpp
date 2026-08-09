#include "musicFavoriteMenu.h"

#include "../application/appMenuManage.h"

#include "../tools/instanceTools.h"
MusicFavoriteMenu::MusicFavoriteMenu( ) {
}
MusicFavoriteMenu::~MusicFavoriteMenu( ) {
	deleteResource( );
}
bool MusicFavoriteMenu::deleteResource( ) {
	return true;
}
bool MusicFavoriteMenu::initBefore( ) {
	deleteResource( );
	return true;
}
bool MusicFavoriteMenu::init( ) {
	return true;
}
bool MusicFavoriteMenu::initAfter( ) {
	return true;
}
bool MusicFavoriteMenu::execMenu( MusicFavoriteWidget *music_list_widget, FavoriteItem *favorite_item, const QPoint &mouse_global_point ) {
	return InstanceTools::getAppMenuManage( )->popMusicFavoriteMenu( mouse_global_point );
}
QMenu * MusicFavoriteMenu::toMenu( ) {
	return this;
}
