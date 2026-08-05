#include "musicToolWidget.h"

#include "../musicCentreWidget.h"
MusicToolWidget::MusicToolWidget( MusicCentreWidget *music_centre_widget ) : QWidget( music_centre_widget ), musicCentreWidget( music_centre_widget ) {
}
bool MusicToolWidget::deleteResource( ) {
	return true;
}
bool MusicToolWidget::initBefore( ) {
	return true;
}
bool MusicToolWidget::init( ) {
	return true;
}
bool MusicToolWidget::initAfter( ) {
	return true;
}
