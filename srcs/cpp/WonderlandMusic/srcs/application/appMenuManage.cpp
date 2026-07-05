#include "appMenuManage.h"

#include "../menu/playerListWidgetMenu.h"
#include "../menu/systemTrayIconMenu.h"

AppMenuManage::AppMenuManage( ) {
}

AppMenuManage::~AppMenuManage( ) {
	deleteResource( );
}

bool AppMenuManage::deleteResource( ) {
	disconnect( );
	Delete_Resource_App_Core_Ptr( playerListWidgetMenu );
	Delete_Resource_App_Core_Ptr( systemTrayIconMenu );
	return true;
}

bool AppMenuManage::initBefore( ) {
	deleteResource( );
	systemTrayIconMenu = new SystemTrayIconMenu;
	playerListWidgetMenu = new PlayerListWidgetMenu;
	return true;
}

bool AppMenuManage::init( ) {
	Before_Init_Resource_App_Core_Ptr( systemTrayIconMenu );
	Before_Init_Resource_App_Core_Ptr( playerListWidgetMenu );

	Init_Resource_App_Core_Ptr( systemTrayIconMenu );
	Init_Resource_App_Core_Ptr( playerListWidgetMenu );

	After_Init_Resource_App_Core_Ptr( systemTrayIconMenu );
	After_Init_Resource_App_Core_Ptr( playerListWidgetMenu );
	return true;
}

bool AppMenuManage::initAfter( ) {
	return true;
}

bool AppMenuManage::popSystemTratIconMenu( const QPoint &pos ) const {
	// todo : 检测空间再配置坐标
	return false;
}

bool AppMenuManage::popPlayerListWidgetMenu( const QPoint &pos ) const {
	// todo : 检测空间再配置坐标
	return false;
}

bool AppMenuManage::popFavoriteWidgetMenu( const QPoint &pos ) const {
	// todo : 检测空间再配置坐标
	return false;
}
