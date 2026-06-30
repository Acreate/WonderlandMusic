#include "appInstance.h"

#include <QSystemTrayIcon>
#include "appDataManage.h"
#include "appDateTimerManage.h"
#include "appDrawManage.h"
#include "appUserInterfaceManage.h"
#include "musicManage.h"

#include "../systemTrayIcon/systemTrayIcon.h"

#include "../tools/templateArgs.h"

#include "../window/mainWindow.h"

AppInstance *AppInstance::instance = nullptr;

AppInstance * AppInstance::getAppInstance( ) {
	return instance;
}

AppInstance::AppInstance( int &argc, char **argv, int app_flag_s ) : QApplication( argc, argv, app_flag_s ) {
}

bool AppInstance::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( appUserInterfaceManage );
	Delete_Resource_App_Core_Ptr( appDrawManage );
	Delete_Resource_App_Core_Ptr( musicManage );
	Delete_Resource_App_Core_Ptr( appDataManage );
	Delete_Resource_App_Core_Ptr( appDateTimerManage );
	instance = nullptr;
	return true;
}

AppDataManage * AppInstance::getAppDataManage( ) const {
	return appDataManage;
}

AppDrawManage * AppInstance::getAppDrawManage( ) const {
	return appDrawManage;
}

AppUserInterfaceManage * AppInstance::getAppUserInterfaceManage( ) const {
	return appUserInterfaceManage;
}

AppDateTimerManage * AppInstance::getAppDateTimerManage( ) const {
	return appDateTimerManage;
}

MusicManage * AppInstance::getMusicManage( ) const {
	return musicManage;
}

AppInstance::~AppInstance( ) {
	deleteResource( );
}

bool AppInstance::notify( QObject *object, QEvent *event ) {
	auto mainWindow = appUserInterfaceManage->getMainWindow( );
	if( object == mainWindow ) {
		auto type = event->type( );
		switch( type ) {
			case QEvent::Close :
				event->ignore( );
				mainWindow->hide( );
				if( QSystemTrayIcon::isSystemTrayAvailable( ) == false )
					quit( );
				return true;
		}
	}
	return QApplication::notify( object, event );
}

bool AppInstance::init( ) {
	deleteResource( );
	instance = this;
	appDateTimerManage = new AppDateTimerManage;
	appDataManage = new AppDataManage;
	musicManage = new MusicManage;
	appDrawManage = new AppDrawManage;
	appUserInterfaceManage = new AppUserInterfaceManage;

	Init_Resource_App_Core_Ptr( appDateTimerManage );
	Init_Resource_App_Core_Ptr( appDataManage );
	Init_Resource_App_Core_Ptr( musicManage );
	Init_Resource_App_Core_Ptr( appDrawManage );
	Init_Resource_App_Core_Ptr( appUserInterfaceManage );

	return true;
}
