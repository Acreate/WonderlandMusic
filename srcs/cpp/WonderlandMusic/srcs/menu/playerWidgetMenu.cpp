#include "playerWidgetMenu.h"

#include "../application/appInstance.h"
#include "../application/appTranslate.h"

#include "../widget/playerListWidget.h"

PlayerWidgetMenu::PlayerWidgetMenu( PlayerListWidget *player_list_widget ) : QMenu( player_list_widget ), playerListWidget( player_list_widget ) {
}

bool PlayerWidgetMenu::initVar( ) {
	appInstance = AppInstance::getAppInstance( );
	if( appInstance == nullptr )
		return false;
	appTranslate = appInstance->getTranslate( );
	if( appTranslate == nullptr )
		return false;
	return true;
}

bool PlayerWidgetMenu::initSubMenu( ) {
	playerMenu = addMenu( appTranslate->getPlayerListMenuenuPlayerMenu( ) );

	controlMenu = addMenu( appTranslate->getPlayerListMenuControlMenu( ) );
	return true;
}

bool PlayerWidgetMenu::initSubMenuAcction( ) {
	setCurrentSelectToPlayerList = playerMenu->QWidget::addAction( appTranslate->getPlayerListMenuPlayerMenuSetCurrentPlayAction( ) );
	insterCurrentSelectToPlayerList = playerMenu->QWidget::addAction( appTranslate->getPlayerListMenuPlayerMenuInsterCurrentPlayAction( ) );
	return true;
}

bool PlayerWidgetMenu::initConnectAcction( ) {
	return true;
}

bool PlayerWidgetMenu::init( ) {
	clear( );
	if( initVar( ) == false )
		return false;
	if( initSubMenu( ) == false )
		return false;
	if( initSubMenuAcction( ) == false )
		return false;
	if( initConnectAcction( ) == false )
		return false;
	return true;
}
