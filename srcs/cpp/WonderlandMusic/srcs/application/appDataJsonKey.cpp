#include "appDataJsonKey.h"
#include "appInstance.h"

#include "../head/init_macro.h"
#include "../head/release_macro.h"

#include "jsonKey/aboutWidgetJsonKey.h"
#include "jsonKey/appDataManageJsonKey.h"
#include "jsonKey/appMusicManageJsonKey.h"
#include "jsonKey/appUserInterfaceManageJsonKey.h"
#include "jsonKey/mainWindowJsonKey.h"
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
