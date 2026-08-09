#include "appMenuManage.h"
#include <qscreen.h>

#include "../head/after_init_macro.h"
#include "../head/before_init_macro.h"
#include "../head/init_macro.h"
#include "../head/release_macro.h"

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
	return true;
}

bool AppMenuManage::initBefore( ) {
	deleteResource( );
	systemTrayIconMenu = new SystemTrayIconMenu;
	Before_Init_Resource_App_Core_Ptr( systemTrayIconMenu );
	return true;
}

bool AppMenuManage::init( ) {
	Init_Resource_App_Core_Ptr( systemTrayIconMenu );

	return true;
}

bool AppMenuManage::initAfter( ) {
	After_Init_Resource_App_Core_Ptr( systemTrayIconMenu );

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

	return true;
}

bool AppMenuManage::popFavoriteWidgetMenu( const QPoint &pos ) const {
	QPoint resutPos;
	if( WidgetTools::getMenuSuggestionShowMenuPos( resutPos, pos, systemTrayIconMenu ) == false )
		return false;

	return true;
}

SystemTrayIconMenu * AppMenuManage::getSystemTrayIconMenu( ) const {
	return systemTrayIconMenu;
}
