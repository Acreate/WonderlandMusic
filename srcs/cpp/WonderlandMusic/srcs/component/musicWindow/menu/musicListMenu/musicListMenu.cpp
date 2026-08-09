#include "musicListMenu.h"
MusicListMenu::MusicListMenu( MusicCentreWidget *music_centre_widget ) : musicCentreWidget( music_centre_widget ) {
}
MusicListMenu::~MusicListMenu( ) {
	deleteResource( );
}
bool MusicListMenu::deleteResource( ) {
	return true;
}
bool MusicListMenu::initBefore( ) {
	return true;
}
bool MusicListMenu::init( ) {
	return true;
}
bool MusicListMenu::initAfter( ) {
	return true;
}
