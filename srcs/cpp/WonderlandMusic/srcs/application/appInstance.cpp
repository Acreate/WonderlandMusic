#include "appInstance.h"

#include "appDataManage.h"
#include "appDateTimerManage.h"
#include "appDrawManage.h"
#include "appMusicManage.h"
#include "appUserInterfaceManage.h"

AppInstance *AppInstance::instance = nullptr;

AppInstance * AppInstance::getAppInstance( ) {
	return instance;
}

AppInstance::AppInstance( int &argc, char **argv, int app_flag_s ) : QApplication( argc, argv, app_flag_s ) {
}

bool AppInstance::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( appUserInterfaceManage );
	Delete_Resource_App_Core_Ptr( appDrawManage );
	Delete_Resource_App_Core_Ptr( appDataManage );
	Delete_Resource_App_Core_Ptr( appMusicManage );
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

AppMusicManage * AppInstance::getAppMusicManage( ) const {
	return appMusicManage;
}

AppInstance::~AppInstance( ) {
	deleteResource( );
}

bool AppInstance::notify( QObject *object, QEvent *event ) {
	return QApplication::notify( object, event );
}

bool AppInstance::init( ) {
	deleteResource( );
	instance = this;
	appDateTimerManage = new AppDateTimerManage;
	appDataManage = new AppDataManage;
	appMusicManage = new AppMusicManage;
	appDrawManage = new AppDrawManage;
	appUserInterfaceManage = new AppUserInterfaceManage;

	Init_Resource_App_Core_Ptr( appDateTimerManage );
	Init_Resource_App_Core_Ptr( appDataManage );
	Init_Resource_App_Core_Ptr( appMusicManage );
	Init_Resource_App_Core_Ptr( appDrawManage );
	Init_Resource_App_Core_Ptr( appUserInterfaceManage );

	return true;
}
