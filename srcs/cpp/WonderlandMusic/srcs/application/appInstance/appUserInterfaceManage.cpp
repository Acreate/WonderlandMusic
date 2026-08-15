#include "appUserInterfaceManage.h"
#include <QJsonObject>

#include "../../head/after_init_macro.h"
#include "../../head/before_init_macro.h"
#include "../../head/init_macro.h"
#include "../../head/release_macro.h"

#include "../../menu/systemTrayIconMenu.h"

#include "../../systemTrayIcon/systemTrayIcon.h"

#include "../../tools/instanceTools.h"
#include "../../tools/pathTools.h"

#include "../../window/mainWindow.h"

#include "appDataManage/jsonKey/appUserInterfaceManageJsonKey.h"

#include "appUserInterfaceManage/appDrawManage.h"
#include "appUserInterfaceManage/appMenuManage.h"

bool AppUserInterfaceManage::deleteResource( ) {
	if( systemTrayIcon )
		systemTrayIcon->hide( );
	Delete_Resource_App_Core_Ptr( appMenuManage );
	Delete_Resource_App_Core_Ptr( mainWindow );
	Delete_Resource_App_Core_Ptr( systemTrayIcon );
	Delete_Resource_App_Core_Ptr( appDrawManage );
	return true;
}

AppMenuManage * AppUserInterfaceManage::getAppMenuManage( ) const {
	return appMenuManage;
}

bool AppUserInterfaceManage::getJsonData( QJsonObject &get_json_object ) const {
	AppJsonKeyTools::getAppUserInterfaceManage( [this, &get_json_object] ( const AppUserInterfaceManageJsonKey &json_key ) {
		QJsonObject writeJsonObject;
		if( getJsonData( writeJsonObject ) == false )
			return false;
		PathTools::writeJsonObject( writeJsonObject, json_key.getFilePath( ) );

		mainWindow->getJsonData( get_json_object );
		return true;
	} );

	return true;
}

bool AppUserInterfaceManage::setJsonData( const QJsonObject &set_json_object ) {
	AppJsonKeyTools::getAppUserInterfaceManage( [this, &set_json_object] ( const AppUserInterfaceManageJsonKey &json_key ) {
		QJsonObject readJson;
		if( PathTools::readJsonObject( readJson, json_key.getFilePath( ) ) == false )
			return false;
		mainWindow->setJsonData( set_json_object );
		return true;
	} );
	return true;
}

bool AppUserInterfaceManage::init( ) {
	Init_Resource_App_Core_Ptr( appDrawManage );
	Init_Resource_App_Core_Ptr( mainWindow );
	Init_Resource_App_Core_Ptr( systemTrayIcon );
	Init_Resource_App_Core_Ptr( appMenuManage );

	return true;
}

bool AppUserInterfaceManage::initBefore( ) {
	deleteResource( );
	appDrawManage = new AppDrawManage;
	mainWindow = new MainWindow;
	systemTrayIcon = new SystemTrayIcon;
	appMenuManage = new AppMenuManage;
	Before_Init_Resource_App_Core_Ptr( appDrawManage );
	Before_Init_Resource_App_Core_Ptr( mainWindow );
	Before_Init_Resource_App_Core_Ptr( systemTrayIcon );
	Before_Init_Resource_App_Core_Ptr( appMenuManage );
	return true;
}

bool AppUserInterfaceManage::initAfter( ) {
	After_Init_Resource_App_Core_Ptr( appDrawManage );
	After_Init_Resource_App_Core_Ptr( mainWindow );
	After_Init_Resource_App_Core_Ptr( systemTrayIcon );
	After_Init_Resource_App_Core_Ptr( appMenuManage );
	if( showMainWindow( ) == false )
		return false;
	systemTrayIcon->show( );

	auto appMenuManage = InstanceTools::getAppMenuManage( );
	auto systemTrayIconMenu = appMenuManage->getSystemTrayIconMenu( );

	connect( systemTrayIconMenu, &SystemTrayIconMenu::signal_show_main_window, this, [this]( ) {
		showMainWindow( );
	} );

	return true;
}

AppUserInterfaceManage::~AppUserInterfaceManage( ) {
	deleteResource( );
}

bool AppUserInterfaceManage::showMainWindow( ) const {
	if( mainWindow == nullptr )
		return false;
	mainWindow->show( );
	mainWindow->raise( );
	mainWindow->activateWindow( );
	return true;
}

bool AppUserInterfaceManage::hideMainWindow( ) const {
	if( mainWindow == nullptr )
		return false;
	mainWindow->hide( );
	return true;
}

MainWindow * AppUserInterfaceManage::getMainWindow( ) const {
	return mainWindow;
}

SystemTrayIcon * AppUserInterfaceManage::getSystemTrayIcon( ) const {
	return systemTrayIcon;
}

AppDrawManage * AppUserInterfaceManage::getAppDrawManage( ) const {
	return appDrawManage;
}
