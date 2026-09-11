#include "playWindow.h"

#include "../../head/release_macro.h"
#include "../../head/result_message_out.h"

#include "../../mutex/userMutex.h"

#include "interface/widget/iPlayerControlWidget.h"
#include "interface/widget/iPlayerWindowCentreWidget.h"

PlayWindow::PlayWindow( QWidget *parent, Qt::WindowFlags flags ) : QMainWindow( parent, flags ) {
	regClassTypeInfoRef( this );
}
PlayWindow::~PlayWindow( ) {
 deleteResource(  );
	
}
bool PlayWindow::deleteResource( ) {
	if( userMutex == nullptr )
		return true;
	userMutex->lock( );
	if( playerWindowCentreWidget )
		playerWindowCentreWidget->setPlayWindow( nullptr );
	takeCentralWidget( );
	playerWindowCentreWidget = nullptr;
	userMutex->unlock( );
	Delete_Resource_App_Core_Ptr( userMutex );
	return true;
}
bool PlayWindow::initBefore( ) {
 deleteResource(  );
	userMutex = new UserMutex;
	return true;
}
bool PlayWindow::init( ) {
	return true;
}
bool PlayWindow::initAfter( ) {
	return true;
}
IPlayerWindowCentreWidget * PlayWindow::getPlayerWindowCentreWidget( ) const {
	return playerWindowCentreWidget;
}
bool PlayWindow::setPlayerWindowCentreWidget( IPlayerWindowCentreWidget *const player_window_centre_widget ) {
	if( playerWindowCentreWidget )
		playerWindowCentreWidget->setPlayWindow( nullptr );
	playerWindowCentreWidget = player_window_centre_widget;
	return true;
}
IPlayerInfoListWidget * PlayWindow::getPlayerInfoListWidget( ) const {
	if( playerWindowCentreWidget == nullptr )
		return nullptr;
	return playerWindowCentreWidget->getPlayerInfoListWidget( );
}
bool PlayWindow::setPlayerInfoListWidget( IPlayerInfoListWidget *player_info_list_widget ) {
	if( playerWindowCentreWidget == nullptr )
		return false;
	return playerWindowCentreWidget->setPlayerInfoListWidget( player_info_list_widget );
}
IPlayerControlWidget * PlayWindow::getPlayerControlWidget( ) const {
	if( playerWindowCentreWidget == nullptr )
		return nullptr;
	return playerWindowCentreWidget->getPlayerControlWidget( );
}
bool PlayWindow::setPlayerControlWidget( IPlayerControlWidget *player_control_widget ) {
	if( playerWindowCentreWidget == nullptr )
		return false;
	return playerWindowCentreWidget->setPlayerControlWidget( player_control_widget );
}
bool PlayWindow::updateLayout( ) {
	if( playerWindowCentreWidget == nullptr )
		return false;
	return playerWindowCentreWidget->updateLayout( );
}
