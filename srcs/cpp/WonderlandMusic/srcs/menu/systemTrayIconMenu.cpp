#include "systemTrayIconMenu.h"

#include "../application/appDataManage.h"
#include "../application/appEventManage.h"
#include "../application/appInstance.h"
#include "../application/appTranslate.h"
#include "../application/appUserInterfaceManage.h"
#include "../application/translate/systemTrayIconMenuTranslate.h"

bool SystemTrayIconMenu::deleteResource( ) {
	clear( );
	return true;
}

bool SystemTrayIconMenu::init( ) {
	if( deleteResource( ) == false )
		return false;
	AppInstance *instance = AppInstance::getAppInstance( );
	auto systemTrayIconMenuTranslate = instance->getAppDataManage( )->getTranslate( )->getSystemTrayIconMenu( );
	auto showMainWindowItem = addAction( systemTrayIconMenuTranslate->getShowMainMenu( ) );
	connect( showMainWindowItem, &QAction::triggered, this, []( ) {
		AppInstance::getAppInstance( )->getAppUserInterfaceManage( )->showMainWindow( );
	} );
	addSeparator( );
	auto quitApp = addAction( systemTrayIconMenuTranslate->getQuitApp( ) );
	connect( quitApp, &QAction::triggered, this, []( ) {
		AppInstance::getAppInstance( )->getAppEventManage( )->quit( );
	} );
	return true;
}

SystemTrayIconMenu::~SystemTrayIconMenu( ) {
	deleteResource( );
}

SystemTrayIconMenu::SystemTrayIconMenu( QWidget *parent ) : SystemTrayIconMenu( "", parent ) {
}

SystemTrayIconMenu::SystemTrayIconMenu( const QString &title, QWidget *parent ) : QMenu( title, parent ) {
}
