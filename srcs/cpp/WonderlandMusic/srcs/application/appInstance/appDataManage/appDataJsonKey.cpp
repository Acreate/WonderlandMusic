#include "appDataJsonKey.h"

#include <head/release_macro.h>

#include <head/init_macro.h>

#include "jsonKey/aboutWidgetJsonKey.h"
#include "jsonKey/appDataManageJsonKey.h"
#include "jsonKey/appMenuManageJsonKey.h"
#include "jsonKey/appMusicManageJsonKey.h"
#include "jsonKey/appUserInterfaceManageJsonKey.h"
#include "jsonKey/favoriteItemJsonKey.h"
#include "jsonKey/mainWindowJsonKey.h"
#include "jsonKey/musicFavoriteMenuJsonKey.h"
#include "jsonKey/musicFavoriteWidgetJsonKey.h"
#include "jsonKey/musicItemJsonKey.h"
#include "jsonKey/musicItemWidthInfoJsonKey.h"
#include "jsonKey/musicListMenuJsonKey.h"
#include "jsonKey/musicWidgetSizeInfoJsonKey.h"
#include "jsonKey/musicWindowJsonKey.h"
#include "jsonKey/systemTrayIconJsonKey.h"

bool AppDataJsonKey::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( aboutWidget );
	Delete_Resource_App_Core_Ptr( mainWindow );
	Delete_Resource_App_Core_Ptr( systemTrayIcon );
	Delete_Resource_App_Core_Ptr( appDataManage );
	Delete_Resource_App_Core_Ptr( appUserInterfaceManage );
	Delete_Resource_App_Core_Ptr( appMusicManage );
	Delete_Resource_App_Core_Ptr( musicWindow );
	Delete_Resource_App_Core_Ptr( musicListMenu );
	Delete_Resource_App_Core_Ptr( musicFavoriteMenu );
	Delete_Resource_App_Core_Ptr( appMenuManage );
	Delete_Resource_App_Core_Ptr( musicItem );
	Delete_Resource_App_Core_Ptr( musicFavoriteWidget );
	Delete_Resource_App_Core_Ptr( favoriteItem );
	Delete_Resource_App_Core_Ptr( musicWidgetSizeInfo );
	Delete_Resource_App_Core_Ptr( musicItemWidthInfo );
	return true;
}

AppDataJsonKey::~AppDataJsonKey( ) {
	deleteResource( );
}

AppDataJsonKey::AppDataJsonKey( ) {
}

bool AppDataJsonKey::init( ) {
	Init_Resource_App_Core_Ptr( aboutWidget );
	Init_Resource_App_Core_Ptr( mainWindow );
	Init_Resource_App_Core_Ptr( systemTrayIcon );
	Init_Resource_App_Core_Ptr( appDataManage );
	Init_Resource_App_Core_Ptr( appUserInterfaceManage );
	Init_Resource_App_Core_Ptr( appMusicManage );
	Init_Resource_App_Core_Ptr( musicWindow );
	Init_Resource_App_Core_Ptr( musicListMenu );
	Init_Resource_App_Core_Ptr( musicFavoriteMenu );
	Init_Resource_App_Core_Ptr( appMenuManage );
	Init_Resource_App_Core_Ptr( musicItem );
	Init_Resource_App_Core_Ptr( musicFavoriteWidget );
	Init_Resource_App_Core_Ptr( favoriteItem );
	Init_Resource_App_Core_Ptr( musicWidgetSizeInfo );
	Init_Resource_App_Core_Ptr( musicItemWidthInfo );
	return true;
}

bool AppDataJsonKey::initBefore( ) {
	deleteResource( );
	aboutWidget = new AboutWidgetJsonKey;
	mainWindow = new MainWindowJsonKey;
	systemTrayIcon = new SystemTrayIconJsonKey;
	appDataManage = new AppDataManageJsonKey;
	appUserInterfaceManage = new AppUserInterfaceManageJsonKey;
	appMusicManage = new AppMusicManageJsonKey;
	musicWindow = new MusicWindowJsonKey;
	musicListMenu = new MusicListMenuJsonKey;
	musicFavoriteMenu = new MusicFavoriteMenuJsonKey;
	appMenuManage = new AppMenuManageJsonKey;

	musicItem = new MusicItemJsonKey;
	musicFavoriteWidget = new MusicFavoriteWidgetJsonKey;
	favoriteItem = new FavoriteItemJsonKey;
	musicWidgetSizeInfo = new MusicWidgetSizeInfoJsonKey;
	musicItemWidthInfo = new MusicItemWidthInfoJsonKey;
	return true;
}

bool AppDataJsonKey::initAfter( ) {
	return true;
}
MusicWindowJsonKey * AppDataJsonKey::getMusicWindow( ) const {
	return musicWindow;
}

AboutWidgetJsonKey * AppDataJsonKey::getAboutWidget( ) const {
	return aboutWidget;
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

AppMusicManageJsonKey * AppDataJsonKey::getAppMusicManage( ) const {
	return appMusicManage;
}
MusicListMenuJsonKey * AppDataJsonKey::getMusicListMenu( ) const {
	return musicListMenu;
}
MusicFavoriteMenuJsonKey * AppDataJsonKey::getMusicFavoriteMenu( ) const {
	return musicFavoriteMenu;
}
AppMenuManageJsonKey * AppDataJsonKey::getAppMenuManage( ) const {
	return appMenuManage;
}
MusicItemJsonKey * AppDataJsonKey::getMusicItem( ) const {
	return musicItem;
}
MusicFavoriteWidgetJsonKey * AppDataJsonKey::getMusicFavoriteWidget( ) const {
	return musicFavoriteWidget;
}
FavoriteItemJsonKey * AppDataJsonKey::getFavoriteItem( ) const {
	return favoriteItem;
}
MusicWidgetSizeInfoJsonKey * AppDataJsonKey::getMusicWidgetSizeInfo( ) const {
	return musicWidgetSizeInfo;
}
MusicItemWidthInfoJsonKey * AppDataJsonKey::getMusicItemWidthInfo( ) const {
	return musicItemWidthInfo;
}
