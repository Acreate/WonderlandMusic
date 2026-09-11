#include "playerControlWidget.h"

#include "../../component/playWindow/interface/widget/iPlayerWindowCentreWidget.h"

PlayerControlWidget::PlayerControlWidget( ) {
	regClassTypeInfoRef( this );
}
PlayerControlWidget::~PlayerControlWidget( ) {
	deleteResource( );
	
}
QWidget * PlayerControlWidget::toWidget( ) {
	return this;
}
bool PlayerControlWidget::setPlayerWindowCentre( IPlayerWindowCentreWidget *play_window ) {
	playerWindowCentreWidget = play_window;
	QWidget *widget = nullptr;
	if( play_window == nullptr )
		widget = play_window->toWidget( );
	setParent( widget );
	if( widget )
		show( );
	else
		hide( );
	return true;
}
IPlayerWindowCentreWidget * PlayerControlWidget::getPlayerWindowCentre( ) const {
	return playerWindowCentreWidget;
}
bool PlayerControlWidget::updateLayout( ) {
	if( playerWindowCentreWidget == nullptr )
		return false;
	auto widget = playerWindowCentreWidget->toWidget( );
	int width = widget->width( );
	resize( width, 200 );
	return true;
}
bool PlayerControlWidget::player( const QString &music_file_path ) {
	return false;
}
bool PlayerControlWidget::stop( ) {
	return false;
}
bool PlayerControlWidget::terminate( ) {
	return false;
}
bool PlayerControlWidget::setPlayerTime( const int64_t &player_mill_second_time ) {
	return false;
}
bool PlayerControlWidget::deleteResource( ) {
	return true;
}
bool PlayerControlWidget::initBefore( ) {
	deleteResource( );
	return true;
}
bool PlayerControlWidget::init( ) {
	return true;
}
bool PlayerControlWidget::initAfter( ) {
	return true;
}
