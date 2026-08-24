#include "musicItemWidget.h"

#include "../../component/musicWindow/musicCentreWidget/musicCentreWidget.h"
MusicItemWidget::MusicItemWidget( ) {
	appendTypeInfo( this );
}
MusicItemWidget::~MusicItemWidget( ) {
}
bool MusicItemWidget::setMusicCentreWidget( MusicCentreWidget *music_centre_widget ) {
	setParent( music_centre_widget );
	musicCentreWidget = music_centre_widget;
	return true;
}
MusicCentreWidget * MusicItemWidget::getMusicCentreWidget( ) const {
	return musicCentreWidget;
}
bool MusicItemWidget::mousePress( const QMouseEvent &mouse_event ) const {
	return false;
}
bool MusicItemWidget::mouseRelease( const QMouseEvent &mouse_event ) const {
	return false;
}
bool MusicItemWidget::drawWidget( ) {
	return false;
}
