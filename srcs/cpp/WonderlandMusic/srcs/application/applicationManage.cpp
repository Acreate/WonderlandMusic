#include "applicationManage.h"

#include "appDataManage.h"
#include "appInstance.h"
#include "appUserInterfaceManage.h"

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
	auto appInstance = AppInstance::getAppInstance( );
	appDataManage = appInstance->getAppDataManage( );
	appUserInterfaceManage = appInstance->getAppUserInterfaceManage( );
	mainWindow = appUserInterfaceManage->getMainWindow( );
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
				appDataManage->writeJsonData( );
				appUserInterfaceManage->writeJsonData( );
				break;
		}
	}
	return QApplication::notify( object, event );
}
