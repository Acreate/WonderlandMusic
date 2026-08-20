#include "musicListMenu.h"

#include "../application/appInstance/appUserInterfaceManage/appMenuManage.h"

#include "../tools/instanceTools.h"
MusicListMenu::MusicListMenu( ) {
	appendTypeInfo( this );
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
bool MusicListMenu::getJsonData( QJsonObject &get_json_object ) const {
	return true;
}
bool MusicListMenu::setJsonData( const QJsonObject &set_json_object ) {
	return true;
}
bool MusicListMenu::setMusicCentreWidget( MusicCentreWidget *music_centre_widget ) {
	return false;
}
bool MusicListMenu::execMenu( IMusicListWidget *music_list_widget, IMusicItem *music_item, const QPoint &mouse_global_point ) {
	return InstanceTools::getAppMenuManage( )->popMusicListMenu( mouse_global_point );
}

QMenu * MusicListMenu::toMenu( ) {
	return this;
}
