#include "musicTitleDockWidget.h"

#include "../musicWindow.h"
MusicTitleDockWidget::MusicTitleDockWidget( MusicWindow *music_window ) : QDockWidget( music_window ), musicWindow( music_window ) {
}
MusicTitleDockWidget::~MusicTitleDockWidget( ) {
	deleteResource( );
}
bool MusicTitleDockWidget::deleteResource( ) {
	return false;
}
bool MusicTitleDockWidget::initBefore( ) {
	return false;
}
bool MusicTitleDockWidget::init( ) {
	return false;
}
bool MusicTitleDockWidget::initAfter( ) {
	return false;
}
