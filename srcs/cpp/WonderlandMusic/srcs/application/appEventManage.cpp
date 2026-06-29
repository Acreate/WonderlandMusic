#include "appEventManage.h"

#include <QSystemTrayIcon>

#include "appInstance.h"
#include "appUserInterfaceManage.h"

#include "../window/mainWindow.h"

bool AppEventManage::deleteResource( ) {
	this->disconnect( );
	appInstance = nullptr;
	execResultCode = 0;
	return true;
}

AppEventManage * AppEventManage::getInstance( ) {
	return AppInstance::getAppInstance( )->getAppEventManage( );
}

bool AppEventManage::init( ) {
	deleteResource( );
	appInstance = AppInstance::getAppInstance( );
	if( appInstance == nullptr )
		return false;
	return true;
}

AppEventManage::~AppEventManage( ) {
	deleteResource( );
}

void AppEventManage::processEvents( ) {
	appInstance->processEvents( );
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
	auto userInterfaceManage = appInstance->getAppUserInterfaceManage( );
	if( userInterfaceManage == nullptr )
		return false;
	MainWindow *window = userInterfaceManage->getMainWindow( );
	if( object == window ) {
		auto type = event->type( );
		switch( type ) {
			case QEvent::Type::Close :
				window->writeWidgetSettingToFile( );
				if( QSystemTrayIcon::isSystemTrayAvailable( ) == false )
					appInstance->quit( ); // 如果不支持托盘，隐藏则退出
				break;
		}
	}
	return false;
}
