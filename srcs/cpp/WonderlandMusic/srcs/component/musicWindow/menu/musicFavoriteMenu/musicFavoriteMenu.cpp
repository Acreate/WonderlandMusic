#include "musicFavoriteMenu.h"

MusicFavoriteMenu::MusicFavoriteMenu( MusicCentreWidget *music_centre_widget ) : musicCentreWidget( music_centre_widget ) {
}
MusicFavoriteMenu::~MusicFavoriteMenu( ) {
	deleteResource( );
}
bool MusicFavoriteMenu::deleteResource( ) {
	return true;
}
void MusicFavoriteMenu::showEvent( QShowEvent *event ) {
	QMenu::showEvent( event );
}
void MusicFavoriteMenu::hideEvent( QHideEvent *hide_event ) {
	QMenu::hideEvent( hide_event );
}
bool MusicFavoriteMenu::initBefore( ) {
	return true;
}
bool MusicFavoriteMenu::init( ) {
	return true;
}
bool MusicFavoriteMenu::initAfter( ) {
	return true;
}
