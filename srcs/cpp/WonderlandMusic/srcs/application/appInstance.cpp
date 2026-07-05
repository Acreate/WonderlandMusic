#include "appInstance.h"

#include "appDataManage.h"
#include "appDateTimerManage.h"
#include "appMenuManage.h"
#include "appUserInterfaceManage.h"



#include "../window/mainWindow.h"

AppInstance *AppInstance::instance = nullptr;

AppInstance * AppInstance::getAppInstance( ) {
	return instance;
}

AppInstance::AppInstance( int &argc, char **argv, int app_flag_s ) : QApplication( argc, argv, app_flag_s ) {
}

bool AppInstance::deleteResource( ) {
	disconnect( );
	Delete_Resource_App_Core_Ptr( appMenuManage );
	Delete_Resource_App_Core_Ptr( appUserInterfaceManage );
	Delete_Resource_App_Core_Ptr( appDataManage );
	Delete_Resource_App_Core_Ptr( appDateTimerManage );
	instance = nullptr;
	return true;
}

AppDataManage * AppInstance::getAppDataManage( ) const {
	return appDataManage;
}

AppUserInterfaceManage * AppInstance::getAppUserInterfaceManage( ) const {
	return appUserInterfaceManage;
}

AppDateTimerManage * AppInstance::getAppDateTimerManage( ) const {
	return appDateTimerManage;
}

AppInstance::~AppInstance( ) {
	deleteResource( );
}

bool AppInstance::notify( QObject *object, QEvent *event ) {
	auto type = event->type( );
	switch( type ) {
		case QEvent::Quit :
			appDataManage->writeJsonData( );
			break;
	}
	return QApplication::notify( object, event );
}

bool AppInstance::init( ) {
	Before_Init_Resource_App_Core_Ptr( appDateTimerManage );
	Before_Init_Resource_App_Core_Ptr( appDataManage );
	Before_Init_Resource_App_Core_Ptr( appUserInterfaceManage );
	Before_Init_Resource_App_Core_Ptr( appMenuManage );

	Init_Resource_App_Core_Ptr( appDateTimerManage );
	Init_Resource_App_Core_Ptr( appDataManage );
	Init_Resource_App_Core_Ptr( appUserInterfaceManage );
	Init_Resource_App_Core_Ptr( appMenuManage );

	After_Init_Resource_App_Core_Ptr( appDateTimerManage );
	After_Init_Resource_App_Core_Ptr( appDataManage );
	After_Init_Resource_App_Core_Ptr( appUserInterfaceManage );
	After_Init_Resource_App_Core_Ptr( appMenuManage );
	return true;
}

bool AppInstance::initBefore( ) {
	deleteResource( );
	instance = this;
	appDateTimerManage = new AppDateTimerManage;
	appDataManage = new AppDataManage;
	appUserInterfaceManage = new AppUserInterfaceManage;
	appMenuManage = new AppMenuManage;
	return true;
}

bool AppInstance::initAfter( ) {
	return true;
}
