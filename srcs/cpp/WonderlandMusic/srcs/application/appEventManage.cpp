#include "appEventManage.h"

#include <QSystemTrayIcon>

#include "appInstance.h"
#include "appUserInterfaceManage.h"

#include "../window/mainWindow.h"

bool AppEventManage::deleteResource( ) {
	appInstance = nullptr;
	execResultCode = 0;
	return true;
}

bool AppEventManage::init( ) {
	deleteResource( );
	appInstance = AppInstance::getAppInstance( );
	if( appInstance == nullptr )
		return false;
	appUserInterfaceManage = appInstance->getAppUserInterfaceManage( );
	if( appUserInterfaceManage == nullptr )
		return false;
	mainWindow = appUserInterfaceManage->getMainWindow( );
	if( mainWindow == nullptr )
		return false;
	appInstance->installEventFilter( this );
	return true;
}

AppEventManage::~AppEventManage( ) {
	deleteResource( );
}

void AppEventManage::processEvents( QEventLoop::ProcessEventsFlags flags ) {
	appInstance->processEvents( flags );
}

void AppEventManage::processEvents( QEventLoop::ProcessEventsFlags flags, int maxtime ) {
	appInstance->processEvents( flags, maxtime );
}

void AppEventManage::processEvents( QEventLoop::ProcessEventsFlags flags, QDeadlineTimer deadline ) {
	appInstance->processEvents( flags, deadline );
}

bool AppEventManage::sendEvent( QObject *receiver, QEvent *event ) {
	return appInstance->sendEvent( receiver, event );;
}

void AppEventManage::postEvent( QObject *receiver, QEvent *event, int priority ) {
	appInstance->postEvent( receiver, event, priority );
}

void AppEventManage::sendPostedEvents( QObject *receiver, int event_type ) {
	appInstance->sendPostedEvents( receiver, event_type );
}

void AppEventManage::removePostedEvents( QObject *receiver, int eventType ) {
	appInstance->removePostedEvents( receiver, eventType );
}

QAbstractEventDispatcher * AppEventManage::eventDispatcher( ) {
	return appInstance->eventDispatcher( );
}

void AppEventManage::setEventDispatcher( QAbstractEventDispatcher *eventDispatcher ) {
	appInstance->setEventDispatcher( eventDispatcher );
}

int AppEventManage::exec( ) {
	execResultCode = appInstance->exec( );
	return execResultCode;
}

void AppEventManage::quit( ) {
	appInstance->quit( );
}

bool AppEventManage::notify( QObject *object, QEvent *event ) {
	if( object == mainWindow ) {
		auto type = event->type( );
		switch( type ) {
			case QEvent::Type::Close :
				mainWindow->writeWidgetSettingToFile( );
				if( QSystemTrayIcon::isSystemTrayAvailable( ) == false )
					appInstance->quit( ); // 如果不支持托盘，隐藏则退出
				break;
		}
	}
	return false;
}
