#include "appUserInterfaceManage.h"
#include "../systemTrayIcon/systemTrayIcon.h"

#include "../window/mainWindow.h"

bool AppUserInterfaceManage::deleteResource( ) {
	delete_ptr( mainWindow, systemTrayIcon );
	return true;
}

bool AppUserInterfaceManage::init( ) {
	deleteResource( );

	if( make_ptr( mainWindow, systemTrayIcon ) == nullptr )
		return false;
	if( make_ptr( mainWindow, systemTrayIcon ) )
		return false;

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
