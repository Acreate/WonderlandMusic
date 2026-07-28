#include "systemTrayIcon.h"
#include <QFileInfo>
#include "../application/appUserInterfaceManage.h"
#include "../application/jsonKey/systemTrayIconJsonKey.h"
#include "../application/translate/systemTrayIconTranslate.h"
#include "../menu/systemTrayIconMenu.h"
#include "../msgInfo/messageErrorOut.h"

#include "../tools/appJsonKeyTools.h"
#include "../tools/appTranslateTools.h"
#include "../tools/instanceTools.h"

#include "../window/mainWindow.h"

bool SystemTrayIcon::deleteResource( ) {
	hide( );
	return true;
}

void SystemTrayIcon::activated_slot( QSystemTrayIcon::ActivationReason reason ) {
	// 单击托盘图标显示/隐藏窗口
	switch( reason ) {
		case Context :
			emit sigal_pop_menu( );
			break;
		case Trigger : {
			MainWindow *mainWindow;
			mainWindow = InstanceTools::getAppUserInterfaceManage( )->getMainWindow( );
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

bool SystemTrayIcon::initBefore( ) {
	if( QSystemTrayIcon::isSystemTrayAvailable( ) == false )
		return false;
	deleteResource( );

	return true;
}

bool SystemTrayIcon::initAfter( ) {
	if( icon( ).isNull( ) )
		if( AppJsonKeyTools::getSystemTrayIcon( [this] ( const SystemTrayIconJsonKey &json_key ) {
			auto logoIconPath = json_key.getIconFilePath( );
			QFileInfo fileInfo( logoIconPath );
			QImage qImage;
			if( fileInfo.exists( ) == false )
				qImage.load( ":/qt-project.org/qmessagebox/images/qtlogo-64.png" );
			else if( qImage.load( logoIconPath ) == false )
				qImage.load( ":/qt-project.org/qmessagebox/images/qtlogo-64.png" );
			auto pixmap = QPixmap::fromImage( qImage );
			QIcon systemTrayIcon( pixmap );
			setIcon( systemTrayIcon );
		} ) == false ) {
			QImage qImage;
			qImage.load( ":/qt-project.org/qmessagebox/images/qtlogo-64.png" );
			auto pixmap = QPixmap::fromImage( qImage );
			QIcon systemTrayIcon( pixmap );
			setIcon( systemTrayIcon );
		}
	if( AppTranslateTools::getSystemTrayIcon( [this] ( SystemTrayIconTranslate &translate ) {
		setToolTip( translate.getAppName( ) );
	} ) == false )
		setToolTip( QObject::tr( "仙村音乐" ) );

	connect( this, &QSystemTrayIcon::activated, this, &SystemTrayIcon::activated_slot );
	return true;
}

bool SystemTrayIcon::init( ) {
	return true;
}

SystemTrayIcon::~SystemTrayIcon( ) {
	deleteResource( );
}
