#include "musicToolDockWidget.h"

#include "../musicWindow.h"
MusicToolDockWidget::MusicToolDockWidget( MusicWindow *music_window ) : QDockWidget( music_window ), musicWindow( music_window ) {
}
MusicToolDockWidget::~MusicToolDockWidget( ) {
	deleteResource( );
}
bool MusicToolDockWidget::deleteResource( ) {
	return false;
}
bool MusicToolDockWidget::initBefore( ) {
	return false;
}
bool MusicToolDockWidget::init( ) {
	return false;
}
bool MusicToolDockWidget::initAfter( ) {
	return false;
}
