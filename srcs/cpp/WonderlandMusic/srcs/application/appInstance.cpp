#include "appInstance.h"

#include "appDataManage.h"
#include "appDateTimerManage.h"
#include "appUserInterfaceManage.h"

#include "../window/mainWindow.h"

AppInstance *AppInstance::instance = nullptr;

AppInstance * AppInstance::getAppInstance( ) {
	return instance;
}

AppInstance::AppInstance( int &argc, char **argv, int app_flag_s ) : QApplication( argc, argv, app_flag_s ) {
}

bool AppInstance::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( appUserInterfaceManage );
	Delete_Resource_App_Core_Ptr( appDataManage );
	Delete_Resource_App_Core_Ptr( appDateTimerManage );
	disconnect( );
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
	deleteResource( );
	instance = this;
	appDateTimerManage = new AppDateTimerManage;
	appDataManage = new AppDataManage;
	appUserInterfaceManage = new AppUserInterfaceManage;

	Init_Resource_App_Core_Ptr( appDateTimerManage );
	Init_Resource_App_Core_Ptr( appDataManage );
	Init_Resource_App_Core_Ptr( appUserInterfaceManage );
	appDataManage->readJsonData( );
	return true;
}
