#include "playerbackProgressBar.h"
bool PlayerbackProgressBar::deleteResource( ) {
	return false;
}
bool PlayerbackProgressBar::initBefore( ) {
	return false;
}
bool PlayerbackProgressBar::init( ) {
	return false;
}
bool PlayerbackProgressBar::initAfter( ) {
	return false;
}
bool PlayerbackProgressBar::setPlayerControlWidget( IPlayerControlWidget *player_control_widget ) {
	return false;
}
QWidget * PlayerbackProgressBar::toWidget( ) {
	return nullptr;
}
bool PlayerbackProgressBar::updateLayout( ) {
	return false;
}
void PlayerbackProgressBar::mouseDoubleClickEvent( QMouseEvent *event ) {
	QWidget::mouseDoubleClickEvent( event );
}
void PlayerbackProgressBar::mouseMoveEvent( QMouseEvent *event ) {
	QWidget::mouseMoveEvent( event );
}
void PlayerbackProgressBar::mousePressEvent( QMouseEvent *event ) {
	QWidget::mousePressEvent( event );
}
void PlayerbackProgressBar::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
}
IPlayerControlWidget * PlayerbackProgressBar::getPlayerControlWidget( ) const {
	return nullptr;
}
bool PlayerbackProgressBar::nextTrack( ) {
	return false;
}
bool PlayerbackProgressBar::previousTrack( ) {
	return false;
}
bool PlayerbackProgressBar::nextPace( ) {
	return false;
}
bool PlayerbackProgressBar::previousPace( ) {
	return false;
}
bool PlayerbackProgressBar::player( ) {
	return false;
}
bool PlayerbackProgressBar::stop( ) {
	return false;
}
bool PlayerbackProgressBar::abort( ) {
	return false;
}
PlayerbackProgressBar::PlayerbackProgressBar( ) {
}
PlayerbackProgressBar::~PlayerbackProgressBar( ) {
	deleteResource( );
}
