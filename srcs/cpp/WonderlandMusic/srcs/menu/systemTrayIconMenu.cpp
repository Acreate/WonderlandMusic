#include "systemTrayIconMenu.h"

#include "../application/appDataManage.h"
#include "../application/appInstance.h"
#include "../application/appTranslate.h"
#include "../application/appUserInterfaceManage.h"
#include "../application/applicationManage.h"
#include "../application/translate/systemTrayIconMenuTranslate.h"

bool SystemTrayIconMenu::deleteResource( ) {
	clear( );
	return true;
}

bool SystemTrayIconMenu::init( ) {
	return true;
}

bool SystemTrayIconMenu::initBefore( ) {
	if( deleteResource( ) == false )
		return false;
	AppInstance *instance = AppInstance::getAppInstance( );
	auto systemTrayIconMenuTranslate = instance->getAppDataManage( )->getTranslate( )->getSystemTrayIconMenu( );

	showMainWindowItem = addAction( systemTrayIconMenuTranslate->getShowMainMenu( ) );
	addSeparator( );
	quitApp = addAction( systemTrayIconMenuTranslate->getQuitApp( ) );
	return true;
}

bool SystemTrayIconMenu::initAfter( ) {
	connect( showMainWindowItem, &QAction::triggered, this, []( ) {
		AppInstance::getAppInstance( )->getAppUserInterfaceManage( )->showMainWindow( );
	} );

	connect( quitApp, &QAction::triggered, this, []( ) {
		AppInstance::getAppInstance( )->getApplicationManage( )->quit( );
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
