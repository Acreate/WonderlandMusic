#include "musicfavoriteWidget.h"
#include "../musicCentreWidget.h"
MusicfavoriteWidget::MusicfavoriteWidget( MusicCentreWidget *music_centre_widget ) : QWidget( music_centre_widget ), musicCentreWidget( music_centre_widget ) {
}
bool MusicfavoriteWidget::deleteResource( ) {
	return true;
}
bool MusicfavoriteWidget::initBefore( ) {
	return true;
}
bool MusicfavoriteWidget::init( ) {
	return true;
}
bool MusicfavoriteWidget::initAfter( ) {
	return true;
}
