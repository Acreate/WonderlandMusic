#include "musicTitleWidget.h"
MusicTitleWidget::MusicTitleWidget( ) {
	appendTypeInfo( this );
}
MusicTitleWidget::~MusicTitleWidget( ) {
	deleteLater( );
}
bool MusicTitleWidget::getJsonData( QJsonObject &get_json_object ) const {
	return false;
}
bool MusicTitleWidget::setJsonData( const QJsonObject &set_json_object ) {
	return false;
}
bool MusicTitleWidget::setMusicCentreWidget( MusicCentreWidget *music_centre_widget ) {
	return false;
}
bool MusicTitleWidget::deleteResource( ) {
	return false;
}
bool MusicTitleWidget::initBefore( ) {
	return false;
}
bool MusicTitleWidget::init( ) {
	return false;
}
bool MusicTitleWidget::initAfter( ) {
	return false;
}
QWidget * MusicTitleWidget::toWidget( ) {
	return nullptr;
}
bool MusicTitleWidget::drawWidgeTarget( QWidget *widget ) {
	return false;
}
MusicCentreWidget * MusicTitleWidget::getMusicCentreWidget( ) const {
	return nullptr;
}
bool MusicTitleWidget::sendMouseMoveEvent( const QMouseEvent &mouse_event ) {
	return false;
}
bool MusicTitleWidget::sendMouseRelaseEvent( const QMouseEvent &mouse_event ) {
	return false;
}
bool MusicTitleWidget::sendMousePressEvent( const QMouseEvent &mouse_event ) {
	return false;
}
