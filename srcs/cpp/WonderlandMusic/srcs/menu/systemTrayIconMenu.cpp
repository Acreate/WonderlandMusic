#include "systemTrayIconMenu.h"

#include "../application/appDataManage.h"
#include "../application/applicationManage.h"
#include "../application/translate/systemTrayIconMenuTranslate.h"

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
	} ) == false )
		return false;
	connect( showMainWindowItem, &QAction::triggered, this, &SystemTrayIconMenu::signal_show_main_window );

	connect( quitApp, &QAction::triggered, this, &SystemTrayIconMenu::signal_quit_app );
	return true;
}

SystemTrayIconMenu::~SystemTrayIconMenu( ) {
	deleteResource( );
}

SystemTrayIconMenu::SystemTrayIconMenu( QWidget *parent ) : SystemTrayIconMenu( "", parent ) {
}

SystemTrayIconMenu::SystemTrayIconMenu( const QString &title, QWidget *parent ) : QMenu( title, parent ) {
}
