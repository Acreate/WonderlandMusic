#include "appUserInterfaceManage.h"

#include "appDrawManage.h"

#include "../systemTrayIcon/systemTrayIcon.h"

#include "../window/mainWindow.h"

bool AppUserInterfaceManage::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( mainWindow );
	Delete_Resource_App_Core_Ptr( systemTrayIcon );
	Delete_Resource_App_Core_Ptr( appDrawManage );
	disconnect( );
	return true;
}

bool AppUserInterfaceManage::init( ) {
	deleteResource( );
	appDrawManage = new AppDrawManage;
	mainWindow = new MainWindow;
	systemTrayIcon = new SystemTrayIcon;
	Init_Resource_App_Core_Ptr( appDrawManage );
	Init_Resource_App_Core_Ptr( mainWindow );
	Init_Resource_App_Core_Ptr( systemTrayIcon );
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

PlayerListTopWidget * AppUserInterfaceManage::getPlayerListTopWidget( ) const {
	return mainWindow->getPlayerListTopWidget( );
}

AppDrawManage * AppUserInterfaceManage::getAppDrawManage( ) const {
	return appDrawManage;
}
