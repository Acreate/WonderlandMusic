#include "systemTrayIcon.h"

#include <QFileInfo>
#include <QMenu>

#include "../application/appDataManage.h"
#include "../application/appInstance.h"
#include "../application/appTranslate.h"
#include "../application/appUserInterfaceManage.h"
#include "../application/jsonFileKey.h"
#include "../application/jsonKey/systemTrayIconJsonKey.h"
#include "../application/translate/systemTrayIconTranslate.h"

#include "../menu/systemTrayIconMenu.h"

#include "../msgInfo/messageErrorOut.h"

#include "../window/mainWindow.h"

bool SystemTrayIcon::deleteResource( ) {
	hide( );
	Delete_Resource_App_Core_Ptr( systemTrayIconMenu );
	return true;
}

void SystemTrayIcon::activated_slot( QSystemTrayIcon::ActivationReason reason ) {
	// 单击托盘图标显示/隐藏窗口
	switch( reason ) {
		case Context : {
			auto point = QCursor::pos( );
			systemTrayIconMenu->adjustSize( );
			int height = systemTrayIconMenu->height( );
			int width = systemTrayIconMenu->width( );
			point = point - QPoint( width, height );
			systemTrayIconMenu->exec( point );
			break;
		}
		case Trigger : {
			AppInstance *appInstance;
			appInstance = AppInstance::getAppInstance( );
			MainWindow *mainWindow;
			mainWindow = appInstance->getAppUserInterfaceManage( )->getMainWindow( );
			mainWindow->show( );
			mainWindow->raise( );
			mainWindow->activateWindow( );
		}
		break;
	}
}

SystemTrayIcon::SystemTrayIcon( QObject *parent ) : SystemTrayIcon( QIcon( ), parent ) {
}

SystemTrayIcon::SystemTrayIcon( const QIcon &icon, QObject *parent ) : QSystemTrayIcon( icon, parent ) {
}

bool SystemTrayIcon::init( ) {
	if( QSystemTrayIcon::isSystemTrayAvailable( ) == false )
		return false;
	if( deleteResource( ) == false )
		return false;
	auto applicationInstance = AppInstance::getAppInstance( );
	auto appDataManage = applicationInstance->getAppDataManage( );
	auto systemTrayIconTranslate = appDataManage->getTranslate( )->getSystemTrayIcon( );
	if( icon( ).isNull( ) ) {
		auto jsonFileKey = appDataManage->getJsonFileKey( );
		auto systemTrayIconJsonKey = jsonFileKey->getSystemTrayIcon( );
		auto logoIconPath = systemTrayIconJsonKey->getIconFilePath( );
		QFileInfo fileInfo( logoIconPath );
		QImage qImage;
		if( fileInfo.exists( ) == false ) {
			Message_Error_Out << systemTrayIconTranslate->getIconFileNotExists( ) + " : " + logoIconPath;
			qImage.load( ":/qt-project.org/qmessagebox/images/qtlogo-64.png" );
		} else if( qImage.load( logoIconPath ) == false ) {
			Message_Error_Out << systemTrayIconTranslate->getIconLoadFileError( ) + " : " + logoIconPath;
			qImage.load( ":/qt-project.org/qmessagebox/images/qtlogo-64.png" );
		}

		auto pixmap = QPixmap::fromImage( qImage );
		QIcon systemTrayIcon( pixmap );
		setIcon( systemTrayIcon );
	}
	systemTrayIconMenu = new SystemTrayIconMenu( );
	if( systemTrayIconMenu->init( ) == false )
		return false;
	setToolTip( systemTrayIconTranslate->getAppName( ) );
	connect( this, &QSystemTrayIcon::activated, this, &SystemTrayIcon::activated_slot );
	show( );
	return true;
}

SystemTrayIcon::~SystemTrayIcon( ) {
	deleteResource( );
}
