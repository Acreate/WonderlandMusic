#include "playerSortOption.h"
void PlayerSortOption::deleteResource( ) {
}
PlayerSortOption::PlayerSortOption( ) {
}
PlayerSortOption::~PlayerSortOption( ) {
	deleteResource( );
}
bool PlayerSortOption::initBefore( ) {
	return false;
}
bool PlayerSortOption::init( ) {
	return false;
}
bool PlayerSortOption::initAfter( ) {
	return false;
}
bool PlayerSortOption::setPlayerControlWidget( IPlayerControlWidget *player_control_widget ) {
	return false;
}
QWidget * PlayerSortOption::toWidget( ) {
	return nullptr;
}
bool PlayerSortOption::updateLayout( ) {
	return false;
}
void PlayerSortOption::mouseDoubleClickEvent( QMouseEvent *event ) {
	QWidget::mouseDoubleClickEvent( event );
}
void PlayerSortOption::mouseMoveEvent( QMouseEvent *event ) {
	QWidget::mouseMoveEvent( event );
}
void PlayerSortOption::mousePressEvent( QMouseEvent *event ) {
	QWidget::mousePressEvent( event );
}
void PlayerSortOption::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
}
IPlayerControlWidget * PlayerSortOption::getPlayerControlWidget( ) const {
	return nullptr;
}
bool PlayerSortOption::sortToMusicName( ) {
	return false;
}
bool PlayerSortOption::sortToMusicSinger( ) {
	return false;
}
bool PlayerSortOption::sortToMusicDuration( ) {
	return false;
}
bool PlayerSortOption::sortToMusicRandom( ) {
	return false;
}
