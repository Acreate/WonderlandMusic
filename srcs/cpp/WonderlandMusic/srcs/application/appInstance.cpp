#include "appInstance.h"

#include "appDataManage.h"
#include "appDateTimerManage.h"
#include "appMenuManage.h"
#include "appUserInterfaceManage.h"
#include "applicationManage.h"

#include "../window/mainWindow.h"

AppInstance *AppInstance::instance = nullptr;

AppInstance::AppParam::~AppParam( ) {
}

AppInstance::AppParam::AppParam( int argc, char **argv, int app_flag_s ) : argc( argc ), argv( argv ), app_flag_s( app_flag_s ) {
}

int AppInstance::AppParam::getArgc( ) const {
	return argc;
}

char ** AppInstance::AppParam::getArgv( ) const {
	return argv;
}

int AppInstance::AppParam::getAppFlagS( ) const {
	return app_flag_s;
}

AppInstance * AppInstance::getAppInstance( ) {
	return instance;
}

AppInstance::AppInstance( int &argc, char **argv, int app_flag_s ) : appParam( argc, argv, app_flag_s ) {
}

bool AppInstance::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( appUserInterfaceManage );
	Delete_Resource_App_Core_Ptr( appDataManage );
	Delete_Resource_App_Core_Ptr( appDateTimerManage );
	Delete_Resource_App_Core_Ptr( applicationManage );
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

ApplicationManage * AppInstance::getApplicationManage( ) const {
	return applicationManage;
}

AppInstance::~AppInstance( ) {
	deleteResource( );
}

bool AppInstance::init( ) {
	Before_Init_Resource_App_Core_Ptr( applicationManage );
	Before_Init_Resource_App_Core_Ptr( appDateTimerManage );
	Before_Init_Resource_App_Core_Ptr( appDataManage );
	Before_Init_Resource_App_Core_Ptr( appUserInterfaceManage );

	Init_Resource_App_Core_Ptr( applicationManage );
	Init_Resource_App_Core_Ptr( appDateTimerManage );
	Init_Resource_App_Core_Ptr( appDataManage );
	Init_Resource_App_Core_Ptr( appUserInterfaceManage );
	
	After_Init_Resource_App_Core_Ptr( appUserInterfaceManage );
	After_Init_Resource_App_Core_Ptr( applicationManage );
	After_Init_Resource_App_Core_Ptr( appDateTimerManage );
	After_Init_Resource_App_Core_Ptr( appDataManage );
	return true;
}

bool AppInstance::initBefore( ) {
	deleteResource( );
	instance = this;
	applicationManage = new ApplicationManage( appParam.argc, appParam.argv, appParam.app_flag_s );
	appDateTimerManage = new AppDateTimerManage;
	appDataManage = new AppDataManage;
	appUserInterfaceManage = new AppUserInterfaceManage;
	return true;
}

bool AppInstance::initAfter( ) {
	appDataManage->readJsonData( );
	appUserInterfaceManage->readJsonData( );
	return true;
}

int AppInstance::exec( ) {
	return applicationManage->exec( );
}
