#include "appDataJsonKey.h"
#include "appInstance.h"
#include "jsonKey/aboutWidgetJsonKey.h"
#include "jsonKey/appDataManageJsonKey.h"
#include "jsonKey/appMusicManageJsonKey.h"
#include "jsonKey/appUserInterfaceManageJsonKey.h"
#include "jsonKey/favorItemWidgetJsonKey.h"
#include "jsonKey/favoriteItemJsonKey.h"
#include "jsonKey/favoriteSrollAreaJsonKey.h"
#include "jsonKey/favoriteWidgetJsonKey.h"
#include "jsonKey/favoritemDockWidgetJsonKey.h"
#include "jsonKey/mainWindowJsonKey.h"
#include "jsonKey/musicInfoItemWidgetJsonKey.h"
#include "jsonKey/musicItemJsonKey.h"
#include "jsonKey/playerListToolWidgetJsonKey.h"
#include "jsonKey/playerListTopWidgetJsonKey.h"
#include "jsonKey/playerWindowJsonKey.h"
#include "jsonKey/systemTrayIconJsonKey.h"

bool AppDataJsonKey::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( playerListToolWidget );
	Delete_Resource_App_Core_Ptr( aboutWidget );
	Delete_Resource_App_Core_Ptr( playerListTopWidget );
	Delete_Resource_App_Core_Ptr( playerWindow );
	Delete_Resource_App_Core_Ptr( mainWindow );
	Delete_Resource_App_Core_Ptr( musicInfoItemWidget );
	Delete_Resource_App_Core_Ptr( systemTrayIcon );
	Delete_Resource_App_Core_Ptr( favoriteSrollArea );
	Delete_Resource_App_Core_Ptr( appDataManage );
	Delete_Resource_App_Core_Ptr( appUserInterfaceManage );
	Delete_Resource_App_Core_Ptr( favoritemDockWidget );
	Delete_Resource_App_Core_Ptr( favoriteWidget );
	Delete_Resource_App_Core_Ptr( appMusicManage );
	Delete_Resource_App_Core_Ptr( favorItemWidget );
	Delete_Resource_App_Core_Ptr( musicItem );
	Delete_Resource_App_Core_Ptr( favoriteItem );
	return true;
}

AppDataJsonKey::~AppDataJsonKey( ) {
	deleteResource( );
}

AppDataJsonKey::AppDataJsonKey( ) {
}

bool AppDataJsonKey::init( ) {
	Init_Resource_App_Core_Ptr( playerListToolWidget );
	Init_Resource_App_Core_Ptr( aboutWidget );
	Init_Resource_App_Core_Ptr( playerListTopWidget );
	Init_Resource_App_Core_Ptr( playerWindow );
	Init_Resource_App_Core_Ptr( mainWindow );
	Init_Resource_App_Core_Ptr( musicInfoItemWidget );
	Init_Resource_App_Core_Ptr( systemTrayIcon );
	Init_Resource_App_Core_Ptr( favoriteSrollArea );
	Init_Resource_App_Core_Ptr( appDataManage );
	Init_Resource_App_Core_Ptr( appUserInterfaceManage );
	Init_Resource_App_Core_Ptr( favoritemDockWidget );
	Init_Resource_App_Core_Ptr( favoriteWidget );
	Init_Resource_App_Core_Ptr( appMusicManage );
	Init_Resource_App_Core_Ptr( favorItemWidget );
	Init_Resource_App_Core_Ptr( musicItem );
	Init_Resource_App_Core_Ptr( favoriteItem );
	return true;
}

bool AppDataJsonKey::initBefore( ) {
	deleteResource( );
	playerListToolWidget = new PlayerListToolWidgetJsonKey;
	aboutWidget = new AboutWidgetJsonKey;
	playerListTopWidget = new PlayerListTopWidgetJsonKey;
	playerWindow = new PlayerWindowJsonKey;
	mainWindow = new MainWindowJsonKey;
	musicInfoItemWidget = new MusicInfoItemWidgetJsonKey;
	systemTrayIcon = new SystemTrayIconJsonKey;
	favoriteSrollArea = new FavoriteSrollAreaJsonKey;
	appDataManage = new AppDataManageJsonKey;
	appUserInterfaceManage = new AppUserInterfaceManageJsonKey;
	favoritemDockWidget = new FavoritemDockWidgetJsonKey;
	favoriteWidget = new FavoriteWidgetJsonKey;
	appMusicManage = new AppMusicManageJsonKey;
	favorItemWidget = new FavorItemWidgetJsonKey;
	musicItem = new MusicItemJsonKey;
	favoriteItem = new FavoriteItemJsonKey;
	return true;
}

bool AppDataJsonKey::initAfter( ) {
	return true;
}

PlayerListToolWidgetJsonKey * AppDataJsonKey::getPlayerListToolWidget( ) const {
	return playerListToolWidget;
}

AboutWidgetJsonKey * AppDataJsonKey::getAboutWidget( ) const {
	return aboutWidget;
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

FavoritemDockWidgetJsonKey * AppDataJsonKey::getFavoritemDockWidget( ) const {
	return favoritemDockWidget;
}

FavoriteWidgetJsonKey * AppDataJsonKey::getFavoriteWidget( ) const {
	return favoriteWidget;
}

AppMusicManageJsonKey * AppDataJsonKey::getAppMusicManage( ) const {
	return appMusicManage;
}

FavorItemWidgetJsonKey * AppDataJsonKey::getFavorItemWidget( ) const {
	return favorItemWidget;
}

MusicItemJsonKey * AppDataJsonKey::getMusicItem( ) const {
	return musicItem;
}

FavoriteItemJsonKey * AppDataJsonKey::getFavoriteItem( ) const {
	return favoriteItem;
}
