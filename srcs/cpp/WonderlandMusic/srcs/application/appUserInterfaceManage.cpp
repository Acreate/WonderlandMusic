#include "appUserInterfaceManage.h"

#include "../msgInfo/messageErrorOut.h"

#include "../systemTrayIcon/systemTrayIcon.h"

#include "../tools/templateArgs.h"

#include "../window/mainWindow.h"

bool AppUserInterfaceManage::deleteResource( ) {
	TemplateArgs::delete_ptr( mainWindow );
	TemplateArgs::delete_ptr( systemTrayIcon );
	return true;
}

bool AppUserInterfaceManage::init( ) {
	deleteResource( );

	if( make_app_core_ptr( mainWindow, systemTrayIcon ) == false )
		return false;
	if( init_app_core_ptr( mainWindow, systemTrayIcon ) == false )
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
