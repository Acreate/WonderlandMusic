#include "appInstance.h"

#include "appDataManage.h"
#include "appDateTimerManage.h"
#include "appDrawManage.h"
#include "appEventManage.h"
#include "appUserInterfaceManage.h"
#include "musicManage.h"

#include "../tools/templateArgs.h"

AppInstance *AppInstance::instance = nullptr;

AppInstance * AppInstance::getAppInstance( ) {
	return instance;
}

AppInstance::AppInstance( int &argc, char **argv, int app_flag_s ) : QApplication( argc, argv, app_flag_s ) {
}

bool AppInstance::deleteResource( ) {
	delete_ptr( appEventManage, appUserInterfaceManage, appDrawManage, musicManage, appDataManage, appDateTimerManage );
	instance = nullptr;
	return true;
}

AppDataManage * AppInstance::getAppDataManage( ) const {
	return appDataManage;
}

AppEventManage * AppInstance::getAppEventManage( ) const {
	return appEventManage;
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
	if( appEventManage && appEventManage->notify( object, event ) == true )
		return true;
	return QApplication::notify( object, event );
}

bool AppInstance::init( ) {
	deleteResource( );
	instance = this;
	if( make_ptr( appDateTimerManage, appDataManage, musicManage, appDrawManage, appUserInterfaceManage, appEventManage ) == nullptr )
		return false;
	if( make_ptr( appEventManage, appDateTimerManage, appDataManage, musicManage, appDrawManage, appUserInterfaceManage ) )
		return false;

	return true;
}
