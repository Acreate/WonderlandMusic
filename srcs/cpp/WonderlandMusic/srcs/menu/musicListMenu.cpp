#include "musicListMenu.h"

#include "../application/appMenuManage.h"

#include "../tools/instanceTools.h"
MusicListMenu::MusicListMenu( ) {
}
MusicListMenu::~MusicListMenu( ) {
	deleteResource( );
}
bool MusicListMenu::deleteResource( ) {
	return true;
}
bool MusicListMenu::initBefore( ) {
	deleteResource( );
	return true;
}
bool MusicListMenu::init( ) {
	return true;
}
bool MusicListMenu::initAfter( ) {
	return true;
}
bool MusicListMenu::execMenu( MusicListWidget *music_list_widget, MusicItem *music_item, const QPoint &mouse_global_point ) {
	
	return InstanceTools::getAppMenuManage(  )->popMusicListMenu( mouse_global_point );
}
QMenu * MusicListMenu::toMenu( ) {
	return this;
}
