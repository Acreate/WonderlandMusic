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
	TemplateArgs::delete_ptr( appEventManage );
	TemplateArgs::delete_ptr( appUserInterfaceManage );
	TemplateArgs::delete_ptr( appDrawManage );
	TemplateArgs::delete_ptr( musicManage );
	TemplateArgs::delete_ptr( appDataManage );
	TemplateArgs::delete_ptr( appDateTimerManage );
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
	if( TemplateArgs::make_ptr( appDateTimerManage ) == nullptr )
		return false;
	if( TemplateArgs::make_ptr( appDataManage ) == nullptr )
		return false;
	if( TemplateArgs::make_ptr( musicManage ) == nullptr )
		return false;
	if( TemplateArgs::make_ptr( appDrawManage ) == nullptr )
		return false;
	if( TemplateArgs::make_ptr( appUserInterfaceManage ) == nullptr )
		return false;
	if( TemplateArgs::make_ptr( appEventManage ) == nullptr )
		return false;

	if( appDateTimerManage->init( ) == false )
		return false;
	if( appDataManage->init( ) == false )
		return false;
	if( musicManage->init( ) == false )
		return false;
	if( appDrawManage->init( ) == false )
		return false;
	if( appUserInterfaceManage->init( ) == false )
		return false;
	if( appUserInterfaceManage->init( ) == false )
		return false;
	if( appEventManage->init( ) == false )
		return false;

	return true;
}
