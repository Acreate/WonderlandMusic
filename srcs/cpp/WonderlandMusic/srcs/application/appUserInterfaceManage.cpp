#include "appUserInterfaceManage.h"

#include <QJsonObject>

#include "appDataJsonKey.h"
#include "appDataManage.h"
#include "appDrawManage.h"
#include "appInstance.h"
#include "appMenuManage.h"

#include "../dockWidget/favoritemDockWidget.h"
#include "../dockWidget/musicItemSizeInfoDockWidget.h"

#include "../scrollArea/favoriteSrollArea.h"

#include "../stackedWidget/mainStackedWidget.h"

#include "../systemTrayIcon/systemTrayIcon.h"

#include "../tools/pathTools.h"

#include "../widget/favoriteWidget.h"
#include "../widget/playerListTopWidget.h"

#include "../window/mainWindow.h"
#include "../window/musicListWindow.h"
#include "../window/playerWindow.h"

#include "jsonKey/appUserInterfaceManageJsonKey.h"

bool AppUserInterfaceManage::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( appMenuManage );
	Delete_Resource_App_Core_Ptr( mainWindow );
	Delete_Resource_App_Core_Ptr( systemTrayIcon );
	Delete_Resource_App_Core_Ptr( appDrawManage );
	disconnect( );
	return true;
}

AppMenuManage * AppUserInterfaceManage::getAppMenuManage( ) const {
	return appMenuManage;
}

bool AppUserInterfaceManage::getJsonData( QJsonObject &get_json_object ) const {
	auto interfaceManage = AppInstance::getAppInstance( )->getAppDataManage( )->getAppDataJsonKey( )->getAppUserInterfaceManage( );
	QJsonObject mainWindowJsonObject;
	bool jsonData = mainWindow->getJsonData( mainWindowJsonObject );
	if( jsonData ) {
		get_json_object.insert( interfaceManage->getMainWindow( ), mainWindowJsonObject );
	}
	mainWindowJsonObject = QJsonObject( );
	auto playerListTopWidget = mainWindow->getMainStackedWidget( )->getPlayerWindow( )->getMusicListWindow( )->getMusicItemSizeInfoDockWidget( )->getPlayerListTopWidget( );
	jsonData = playerListTopWidget->getJsonData( mainWindowJsonObject );
	if( jsonData ) {
		get_json_object.insert( interfaceManage->getMusicListTopDockWidget( ), mainWindowJsonObject );
	}
	return true;
}

bool AppUserInterfaceManage::setJsonData( const QJsonObject &set_json_object ) {
	auto interfaceManage = AppInstance::getAppInstance( )->getAppDataManage( )->getAppDataJsonKey( )->getAppUserInterfaceManage( );
	auto find = set_json_object.find( interfaceManage->getMainWindow( ) );
	auto end = set_json_object.end( );
	if( find != end ) {
		auto jsonValueRefs = find.value( ).toObject( );
		mainWindow->setJsonData( jsonValueRefs );
	}
	find = set_json_object.find( interfaceManage->getMusicListTopDockWidget( ) );
	if( find != end ) {
		auto jsonValueRefs = find.value( ).toObject( );
		auto playerListTopWidget = mainWindow->getMainStackedWidget( )->getPlayerWindow( )->getMusicListWindow( )->getMusicItemSizeInfoDockWidget( )->getPlayerListTopWidget( );
		playerListTopWidget->setJsonData( jsonValueRefs );
	}
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
	Before_Init_Resource_App_Core_Ptr( appDrawManage );
	Before_Init_Resource_App_Core_Ptr( mainWindow );
	Before_Init_Resource_App_Core_Ptr( systemTrayIcon );
	Before_Init_Resource_App_Core_Ptr( appMenuManage );

	Init_Resource_App_Core_Ptr( appDrawManage );
	Init_Resource_App_Core_Ptr( mainWindow );
	Init_Resource_App_Core_Ptr( systemTrayIcon );
	Init_Resource_App_Core_Ptr( appMenuManage );

	After_Init_Resource_App_Core_Ptr( appDrawManage );
	After_Init_Resource_App_Core_Ptr( mainWindow );
	After_Init_Resource_App_Core_Ptr( systemTrayIcon );
	After_Init_Resource_App_Core_Ptr( appMenuManage );
	return true;
}

bool AppUserInterfaceManage::initBefore( ) {
	deleteResource( );
	appDrawManage = new AppDrawManage;
	mainWindow = new MainWindow;
	systemTrayIcon = new SystemTrayIcon;
	appMenuManage = new AppMenuManage;
	return true;
}

bool AppUserInterfaceManage::initAfter( ) {
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

AppDrawManage * AppUserInterfaceManage::getAppDrawManage( ) const {
	return appDrawManage;
}

bool AppUserInterfaceManage::appendFavoriteItem( const QString &create_favorite_name ) {
	auto favoriteWidget = mainWindow->getMainStackedWidget( )->getPlayerWindow( )->getFavoritemDockWidget( )->getFavoriteSrollArea( )->getFavoriteWidget( );
	return favoriteWidget->appendFavoriteItem( create_favorite_name );
}

bool AppUserInterfaceManage::removeFavoriteItem( const QString &remove_favorite_name ) {
	auto favoriteWidget = mainWindow->getMainStackedWidget( )->getPlayerWindow( )->getFavoritemDockWidget( )->getFavoriteSrollArea( )->getFavoriteWidget( );
	return favoriteWidget->removeFavoriteItem( remove_favorite_name );
}

bool AppUserInterfaceManage::resetFavoriteItem( const std::vector< QString > &create_favorite_vector ) {
	auto favoriteWidget = mainWindow->getMainStackedWidget( )->getPlayerWindow( )->getFavoritemDockWidget( )->getFavoriteSrollArea( )->getFavoriteWidget( );
	return favoriteWidget->resetFavoriteItem( create_favorite_vector );
}
