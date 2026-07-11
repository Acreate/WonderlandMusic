#include "appUserInterfaceManage.h"
#include <QJsonObject>
#include "appDataJsonKey.h"
#include "appDataManage.h"
#include "appDrawManage.h"
#include "appInstance.h"
#include "appMenuManage.h"
#include "applicationManage.h"
#include "../menu/systemTrayIconMenu.h"
#include "../systemTrayIcon/systemTrayIcon.h"
#include "../tools/pathTools.h"
#include "../window/addFavoriteWindow.h"
#include "../window/mainWindow.h"
#include "../window/musicListWindow.h"
#include "jsonKey/appUserInterfaceManageJsonKey.h"

bool AppUserInterfaceManage::deleteResource( ) {
	if( systemTrayIcon )
		systemTrayIcon->hide( );
	Delete_Resource_App_Core_Ptr( appMenuManage );
	Delete_Resource_App_Core_Ptr( addFavoriteWindow );
	Delete_Resource_App_Core_Ptr( mainWindow );
	Delete_Resource_App_Core_Ptr( systemTrayIcon );
	Delete_Resource_App_Core_Ptr( appDrawManage );
	return true;
}

AppMenuManage * AppUserInterfaceManage::getAppMenuManage( ) const {
	return appMenuManage;
}

bool AppUserInterfaceManage::getJsonData( QJsonObject &get_json_object ) const {
	mainWindow->getJsonData( get_json_object );

	return true;
}

bool AppUserInterfaceManage::setJsonData( const QJsonObject &set_json_object ) {
	mainWindow->setJsonData( set_json_object );
	return true;
}

bool AppUserInterfaceManage::readJsonData( ) {
	auto interfaceManage = AppInstance::getAppInstance( )->getAppDataManage( )->getAppDataJsonKey( )->getAppUserInterfaceManage( );
	QJsonObject readJson;
	if( PathTools::readJsonObject( readJson, interfaceManage->getFilePath( ) ) ) {
		setJsonData( readJson );
	}

	return true;
}

bool AppUserInterfaceManage::writeJsonData( ) {
	QJsonObject writeJsonObject;
	if( getJsonData( writeJsonObject ) ) {
		auto interfaceManage = AppInstance::getAppInstance( )->getAppDataManage( )->getAppDataJsonKey( )->getAppUserInterfaceManage( );
		PathTools::writeJsonObject( writeJsonObject, interfaceManage->getFilePath( ) );
	}
	return true;
}

bool AppUserInterfaceManage::init( ) {
	Init_Resource_App_Core_Ptr( appDrawManage );
	Init_Resource_App_Core_Ptr( addFavoriteWindow );
	Init_Resource_App_Core_Ptr( mainWindow );
	Init_Resource_App_Core_Ptr( systemTrayIcon );
	Init_Resource_App_Core_Ptr( appMenuManage );

	return true;
}

bool AppUserInterfaceManage::initBefore( ) {
	deleteResource( );
	appDrawManage = new AppDrawManage;
	addFavoriteWindow = new AddFavoriteWindow;
	mainWindow = new MainWindow;
	systemTrayIcon = new SystemTrayIcon;
	appMenuManage = new AppMenuManage;
	Before_Init_Resource_App_Core_Ptr( appDrawManage );
	Before_Init_Resource_App_Core_Ptr( addFavoriteWindow );
	Before_Init_Resource_App_Core_Ptr( mainWindow );
	Before_Init_Resource_App_Core_Ptr( systemTrayIcon );
	Before_Init_Resource_App_Core_Ptr( appMenuManage );
	return true;
}

bool AppUserInterfaceManage::initAfter( ) {
	After_Init_Resource_App_Core_Ptr( appDrawManage );
	After_Init_Resource_App_Core_Ptr( addFavoriteWindow );
	After_Init_Resource_App_Core_Ptr( mainWindow );
	After_Init_Resource_App_Core_Ptr( systemTrayIcon );
	After_Init_Resource_App_Core_Ptr( appMenuManage );
	if( showMainWindow( ) == false )
		return false;
	systemTrayIcon->show( );

	auto instance = AppInstance::getAppInstance( );
	auto appMenuManage = instance->getAppUserInterfaceManage( )->getAppMenuManage( );
	auto systemTrayIconMenu = appMenuManage->getSystemTrayIconMenu( );

	connect( systemTrayIconMenu, &SystemTrayIconMenu::signal_show_main_window, this, [this]( ) {
		showMainWindow( );
	} );

	return true;
}

AppUserInterfaceManage::~AppUserInterfaceManage( ) {
	deleteResource( );
}

AddFavoriteWindow * AppUserInterfaceManage::getAddFavoriteWindow( ) const {
	return addFavoriteWindow;
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
