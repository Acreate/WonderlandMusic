#include "musicTitleWidget.h"
MusicTitleWidget::MusicTitleWidget( ) {
	appendTypeInfo( this );
}
MusicTitleWidget::~MusicTitleWidget( ) {
	deleteLater( );
}
bool MusicTitleWidget::getJsonData( QJsonObject &get_json_object ) const {
	return true;
}
bool MusicTitleWidget::setJsonData( const QJsonObject &set_json_object ) {
	return true;
}
bool MusicTitleWidget::setMusicCentreWidget( MusicCentreWidget *music_centre_widget ) {
	musicCentreWidget = music_centre_widget;
	return true;
}
bool MusicTitleWidget::deleteResource( ) {
	return true;
}
bool MusicTitleWidget::initBefore( ) {
	return true;
}
bool MusicTitleWidget::init( ) {
	return true;
}
bool MusicTitleWidget::initAfter( ) {
	return true;
}
QWidget * MusicTitleWidget::toWidget( ) {
	return this;
}
bool MusicTitleWidget::drawWidgeTarget( QWidget *widget ) {
	return true;
}
MusicCentreWidget * MusicTitleWidget::getMusicCentreWidget( ) const {
	return musicCentreWidget;
}
bool MusicTitleWidget::sendMouseMoveEvent( const QMouseEvent &mouse_event ) {
	return true;
}
bool MusicTitleWidget::sendMouseRelaseEvent( const QMouseEvent &mouse_event ) {
	return true;
}
bool MusicTitleWidget::sendMousePressEvent( const QMouseEvent &mouse_event ) {
	return true;
}
