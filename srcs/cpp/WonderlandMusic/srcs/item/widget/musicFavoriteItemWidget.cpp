#include "musicFavoriteItemWidget.h"

#include "../../component/musicWindow/musicCentreWidget/musicCentreWidget.h"
MusicFavoriteItemWidget::MusicFavoriteItemWidget( ) {
	appendTypeInfo( this );
}
MusicFavoriteItemWidget::~MusicFavoriteItemWidget( ) {
}
bool MusicFavoriteItemWidget::setMusicCentreWidget( MusicCentreWidget *music_centre_widget ) {
	setParent( music_centre_widget );
	musicCentreWidget = music_centre_widget;
	return true;
}
MusicCentreWidget * MusicFavoriteItemWidget::getMusicCentreWidget( ) const {
	return musicCentreWidget;
}
bool MusicFavoriteItemWidget::mousePress( const QMouseEvent &mouse_event ) const {
	return false;
}
bool MusicFavoriteItemWidget::mouseRelease( const QMouseEvent &mouse_event ) const {
	return false;
}
bool MusicFavoriteItemWidget::drawWidget( ) {
	return false;
}
