#include "playerSelectOption.h"
bool PlayerSelectOption::deleteResource( ) {
	return false;
}
bool PlayerSelectOption::initBefore( ) {
	return false;
}
bool PlayerSelectOption::init( ) {
	return false;
}
bool PlayerSelectOption::initAfter( ) {
	return false;
}
bool PlayerSelectOption::setPlayerControlWidget( IPlayerControlWidget *player_control_widget ) {
	return false;
}
QWidget * PlayerSelectOption::toWidget( ) {
	return nullptr;
}
bool PlayerSelectOption::updateLayout( ) {
	return false;
}
IPlayerControlWidget * PlayerSelectOption::getPlayerControlWidget( ) const {
	return nullptr;
}
bool PlayerSelectOption::nextTrack( ) {
	return false;
}
bool PlayerSelectOption::previousTrack( ) {
	return false;
}
bool PlayerSelectOption::nextPace( ) {
	return false;
}
bool PlayerSelectOption::previousPace( ) {
	return false;
}
bool PlayerSelectOption::player( ) {
	return false;
}
bool PlayerSelectOption::stop( ) {
	return false;
}
bool PlayerSelectOption::abort( ) {
	return false;
}
void PlayerSelectOption::mouseDoubleClickEvent( QMouseEvent *event ) {
	QWidget::mouseDoubleClickEvent( event );
}
void PlayerSelectOption::mouseMoveEvent( QMouseEvent *event ) {
	QWidget::mouseMoveEvent( event );
}
void PlayerSelectOption::mousePressEvent( QMouseEvent *event ) {
	QWidget::mousePressEvent( event );
}
void PlayerSelectOption::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
}
