#include "musicListWidget.h"
#include "../musicCentreWidget.h"
MusicListWidget::MusicListWidget( MusicCentreWidget *music_centre_widget ) : QWidget( music_centre_widget ), musicCentreWidget( music_centre_widget ) {
}
bool MusicListWidget::deleteResource( ) {
	return true;
}
bool MusicListWidget::initBefore( ) {
	return true;
}
bool MusicListWidget::init( ) {
	return true;
}
bool MusicListWidget::initAfter( ) {
	return true;
}
