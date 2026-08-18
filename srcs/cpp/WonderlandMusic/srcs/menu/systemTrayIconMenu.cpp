#include "systemTrayIconMenu.h"

#include "../application/appInstance/appUserInterfaceManage.h"
#include "../application/appInstance/applicationManage.h"
#include "../application/appInstance/appDataManage/translate/systemTrayIconMenuTranslate.h"

#include "../tools/instanceTools.h"

void SystemTrayIconMenu::slot_showMainWindow( ) {
	auto appUserInterfaceManage = InstanceTools::getAppUserInterfaceManage( );
	if( appUserInterfaceManage == nullptr )
		return;
	appUserInterfaceManage->showMainWindow( );
}
void SystemTrayIconMenu::slot_quitApp( ) {
	auto applicationManage = InstanceTools::getApplicationManage( );
	if( applicationManage == nullptr )
		return;
	applicationManage->quit( );
}
bool SystemTrayIconMenu::deleteResource( ) {
	clear( );
	return true;
}

bool SystemTrayIconMenu::init( ) {
	showMainWindowItem = addAction( "" );
	addSeparator( );
	quitApp = addAction( "" );
	return true;
}

bool SystemTrayIconMenu::initBefore( ) {
	deleteResource( );

	return true;
}

bool SystemTrayIconMenu::initAfter( ) {
	if( AppTranslateTools::getSystemTrayIconMenu( [this] ( SystemTrayIconMenuTranslate &translate ) {
		showMainWindowItem->setText( translate.getShowMainMenu( ) );
		quitApp->setText( translate.getQuitApp( ) );
		return true;
	} ) == false )
		return false;
	connect( showMainWindowItem, &QAction::triggered, this, &SystemTrayIconMenu::slot_showMainWindow );

	connect( quitApp, &QAction::triggered, this, &SystemTrayIconMenu::slot_quitApp );
	return true;
}

SystemTrayIconMenu::~SystemTrayIconMenu( ) {
	deleteResource( );
}

SystemTrayIconMenu::SystemTrayIconMenu( QWidget *parent ) : SystemTrayIconMenu( "", parent ) {
}

SystemTrayIconMenu::SystemTrayIconMenu( const QString &title, QWidget *parent ) : QMenu( title, parent ) {
}
