#include "appMenuManage.h"

#include <qscreen.h>

#include "appInstance.h"

#include "../menu/favoriteWidgetMenu.h"
#include "../menu/playerListWidgetMenu.h"
#include "../menu/systemTrayIconMenu.h"

#include "../tools/widgetTools.h"

AppMenuManage::AppMenuManage( ) {
}

AppMenuManage::~AppMenuManage( ) {
	deleteResource( );
}

bool AppMenuManage::deleteResource( ) {
	disconnect( );
	Delete_Resource_App_Core_Ptr( favoriteWidgetMenu );
	Delete_Resource_App_Core_Ptr( playerListWidgetMenu );
	Delete_Resource_App_Core_Ptr( systemTrayIconMenu );
	return true;
}

bool AppMenuManage::initBefore( ) {
	deleteResource( );
	systemTrayIconMenu = new SystemTrayIconMenu;
	playerListWidgetMenu = new PlayerListWidgetMenu;
	favoriteWidgetMenu = new FavoriteWidgetMenu;
	Before_Init_Resource_App_Core_Ptr( systemTrayIconMenu );
	Before_Init_Resource_App_Core_Ptr( playerListWidgetMenu );
	Before_Init_Resource_App_Core_Ptr( favoriteWidgetMenu );
	return true;
}

bool AppMenuManage::init( ) {
	Init_Resource_App_Core_Ptr( systemTrayIconMenu );
	Init_Resource_App_Core_Ptr( playerListWidgetMenu );
	Init_Resource_App_Core_Ptr( favoriteWidgetMenu );

	return true;
}

bool AppMenuManage::initAfter( ) {
	After_Init_Resource_App_Core_Ptr( systemTrayIconMenu );
	After_Init_Resource_App_Core_Ptr( playerListWidgetMenu );
	After_Init_Resource_App_Core_Ptr( favoriteWidgetMenu );
	return true;
}

bool AppMenuManage::popSystemTratIconMenu( const QPoint &pos ) const {
	QPoint resutPos;
	if( WidgetTools::getMenuSuggestionShowMenuPos( resutPos, pos, systemTrayIconMenu ) == false )
		return false;
	systemTrayIconMenu->exec( resutPos );
	return true;
}

bool AppMenuManage::popPlayerListWidgetMenu( const QPoint &pos ) const {
	QPoint resutPos;
	if( WidgetTools::getMenuSuggestionShowMenuPos( resutPos, pos, systemTrayIconMenu ) == false )
		return false;
	playerListWidgetMenu->exec( resutPos );
	return true;
}

bool AppMenuManage::popFavoriteWidgetMenu( const QPoint &pos ) const {
	QPoint resutPos;
	if( WidgetTools::getMenuSuggestionShowMenuPos( resutPos, pos, systemTrayIconMenu ) == false )
		return false;
	favoriteWidgetMenu->exec( resutPos );
	return true;
}

SystemTrayIconMenu * AppMenuManage::getSystemTrayIconMenu( ) const {
	return systemTrayIconMenu;
}

PlayerListWidgetMenu * AppMenuManage::getPlayerListWidgetMenu( ) const {
	return playerListWidgetMenu;
}

FavoriteWidgetMenu * AppMenuManage::getFavoriteWidgetMenu( ) const {
	return favoriteWidgetMenu;
}
