#include "appMenuManage.h"
#include <qscreen.h>

#include "../head/after_init_macro.h"
#include "../head/before_init_macro.h"
#include "../head/init_macro.h"
#include "../head/release_macro.h"

#include "../menu/musicFavoriteMenu.h"
#include "../menu/musicListMenu.h"
#include "../menu/systemTrayIconMenu.h"
#include "../tools/widgetTools.h"
#include "../window/mainWindow.h"

AppMenuManage::AppMenuManage( ) {
}

AppMenuManage::~AppMenuManage( ) {
	deleteResource( );
}

bool AppMenuManage::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( systemTrayIconMenu );
	Delete_Resource_App_Core_Ptr( musicFavoriteMenu );
	Delete_Resource_App_Core_Ptr( musicListMenu );
	return true;
}

bool AppMenuManage::initBefore( ) {
	deleteResource( );
	systemTrayIconMenu = new SystemTrayIconMenu;
	musicFavoriteMenu = new MusicFavoriteMenu;
	musicListMenu = new MusicListMenu;
	Before_Init_Resource_App_Core_Ptr( systemTrayIconMenu );
	Before_Init_Resource_App_Core_Ptr( musicFavoriteMenu );
	Before_Init_Resource_App_Core_Ptr( musicListMenu );
	return true;
}

bool AppMenuManage::init( ) {
	Init_Resource_App_Core_Ptr( systemTrayIconMenu );
	Init_Resource_App_Core_Ptr( musicFavoriteMenu );
	Init_Resource_App_Core_Ptr( musicListMenu );

	return true;
}

bool AppMenuManage::initAfter( ) {
	After_Init_Resource_App_Core_Ptr( systemTrayIconMenu );
	After_Init_Resource_App_Core_Ptr( musicFavoriteMenu );
	After_Init_Resource_App_Core_Ptr( musicListMenu );
	return true;
}

bool AppMenuManage::popSystemTratIconMenu( const QPoint &pos ) const {
	QPoint resutPos;
	if( WidgetTools::getMenuSuggestionShowMenuPos( resutPos, pos, systemTrayIconMenu ) == false )
		return false;
	systemTrayIconMenu->exec( resutPos );
	return true;
}
bool AppMenuManage::popMusicFavoriteMenu( const QPoint &pos ) const {
	QPoint resutPos;
	auto menu = musicFavoriteMenu->toMenu( );
	if( menu == nullptr )
		return false;
	if( WidgetTools::getMenuSuggestionShowMenuPos( resutPos, pos, menu ) == false )
		return false;
	menu->exec( resutPos );
	return true;
}
bool AppMenuManage::popMusicListMenu( const QPoint &pos ) const {
	QPoint resutPos;
	auto menu = musicListMenu->toMenu( );
	if( menu == nullptr )
		return false;
	if( WidgetTools::getMenuSuggestionShowMenuPos( resutPos, pos, menu ) == false )
		return false;
	menu->exec( resutPos );
	return true;
}

SystemTrayIconMenu * AppMenuManage::getSystemTrayIconMenu( ) const {
	return systemTrayIconMenu;
}
IMusicFavoriteMenu * AppMenuManage::getMusicFavoriteMenu( ) const {
	return musicFavoriteMenu;
}
IMusicListMenu * AppMenuManage::getMusicListMenu( ) const {
	return musicListMenu;
}
