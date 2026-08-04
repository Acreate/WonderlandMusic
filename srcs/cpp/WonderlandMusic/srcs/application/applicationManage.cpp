#include "applicationManage.h"

#include "appDataManage.h"
#include "appUserInterfaceManage.h"

#include "../tools/instanceTools.h"

#include "../window/mainWindow.h"

bool ApplicationManage::deleteResource( ) {
	return true;
}

bool ApplicationManage::initBefore( ) {
	return true;
}

bool ApplicationManage::init( ) {
	return true;
}

bool ApplicationManage::initAfter( ) {
	appUserInterfaceManage = InstanceTools::getAppUserInterfaceManage( );
	mainWindow = appUserInterfaceManage->getMainWindow( );
	appDataManage = InstanceTools::getAppDataManage( );
	return true;
}

ApplicationManage::ApplicationManage( int &argc, char **argv, int app_flag_s ) : QApplication( argc, argv, app_flag_s ) {
}

ApplicationManage::~ApplicationManage( ) {
	deleteResource( );
}

bool ApplicationManage::notify( QObject *object, QEvent *event ) {
	if( mainWindow && object == mainWindow ) {
		auto type = event->type( );
		switch( type ) {
			case QEvent::Close :
				appUserInterfaceManage->writeJsonData( );
				break;
			case QEvent::Quit :
				appDataManage->writeJsonData( );
				emit signal_app_quit( );
				break;
		}
	}
	return QApplication::notify( object, event );
}
