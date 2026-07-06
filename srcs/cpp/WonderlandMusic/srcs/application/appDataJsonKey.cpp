#include "appDataJsonKey.h"

#include "appInstance.h"

#include "jsonKey/aboutWidgetJsonKey.h"
#include "jsonKey/appDataManageJsonKey.h"
#include "jsonKey/appUserInterfaceManageJsonKey.h"
#include "jsonKey/favoriteSrollAreaJsonKey.h"
#include "jsonKey/mainWindowJsonKey.h"
#include "jsonKey/musicInfoItemWidgetJsonKey.h"
#include "jsonKey/playerListToolWidgetJsonKey.h"
#include "jsonKey/playerListTopWidgetJsonKey.h"
#include "jsonKey/playerWindowJsonKey.h"
#include "jsonKey/systemTrayIconJsonKey.h"

bool AppDataJsonKey::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( playerListToolWidget );
	Delete_Resource_App_Core_Ptr( aboutWidgetJsonFileKey );
	Delete_Resource_App_Core_Ptr( playerListTopWidget );
	Delete_Resource_App_Core_Ptr( playerWindow );
	Delete_Resource_App_Core_Ptr( mainWindow );
	Delete_Resource_App_Core_Ptr( musicInfoItemWidget );
	Delete_Resource_App_Core_Ptr( systemTrayIcon );
	Delete_Resource_App_Core_Ptr( favoriteSrollArea );
	Delete_Resource_App_Core_Ptr( appDataManage );
	Delete_Resource_App_Core_Ptr( appUserInterfaceManage );
	return true;
}

AppDataJsonKey::~AppDataJsonKey( ) {
	deleteResource( );
}

AppDataJsonKey::AppDataJsonKey( ) {
}

bool AppDataJsonKey::init( ) {
	Init_Resource_App_Core_Ptr( playerListToolWidget );
	Init_Resource_App_Core_Ptr( aboutWidgetJsonFileKey );
	Init_Resource_App_Core_Ptr( playerListTopWidget );
	Init_Resource_App_Core_Ptr( playerWindow );
	Init_Resource_App_Core_Ptr( mainWindow );
	Init_Resource_App_Core_Ptr( musicInfoItemWidget );
	Init_Resource_App_Core_Ptr( systemTrayIcon );
	Init_Resource_App_Core_Ptr( favoriteSrollArea );
	Init_Resource_App_Core_Ptr( appDataManage );
	Init_Resource_App_Core_Ptr( appUserInterfaceManage );
	return true;
}

bool AppDataJsonKey::initBefore( ) {
	deleteResource( );
	playerListToolWidget = new PlayerListToolWidgetJsonKey;
	aboutWidgetJsonFileKey = new AboutWidgetJsonKey;
	playerListTopWidget = new PlayerListTopWidgetJsonKey;
	playerWindow = new PlayerWindowJsonKey;
	mainWindow = new MainWindowJsonKey;
	musicInfoItemWidget = new MusicInfoItemWidgetJsonKey;
	systemTrayIcon = new SystemTrayIconJsonKey;
	favoriteSrollArea = new FavoriteSrollAreaJsonKey;
	appDataManage = new AppDataManageJsonKey;
	appUserInterfaceManage = new AppUserInterfaceManageJsonKey;
	return true;
}

bool AppDataJsonKey::initAfter( ) {
	return true;
}

PlayerListToolWidgetJsonKey * AppDataJsonKey::getPlayerListToolWidget( ) const {
	return playerListToolWidget;
}

AboutWidgetJsonKey * AppDataJsonKey::getAboutWidgetJsonFileKey( ) const {
	return aboutWidgetJsonFileKey;
}

PlayerListTopWidgetJsonKey * AppDataJsonKey::getPlayerListTopWidget( ) const {
	return playerListTopWidget;
}

PlayerWindowJsonKey * AppDataJsonKey::getPlayerWindow( ) const {
	return playerWindow;
}

MusicInfoItemWidgetJsonKey * AppDataJsonKey::getMusicInfoItemWidget( ) const {
	return musicInfoItemWidget;
}

MainWindowJsonKey * AppDataJsonKey::getMainWindow( ) const {
	return mainWindow;
}

SystemTrayIconJsonKey * AppDataJsonKey::getSystemTrayIcon( ) const {
	return systemTrayIcon;
}

AppDataManageJsonKey * AppDataJsonKey::getAppDataManage( ) const {
	return appDataManage;
}

AppUserInterfaceManageJsonKey * AppDataJsonKey::getAppUserInterfaceManage( ) const {
	return appUserInterfaceManage;
}

FavoriteSrollAreaJsonKey * AppDataJsonKey::getFavoriteSrollArea( ) const {
	return favoriteSrollArea;
}
