#include "appInstance.h"

#include <QDateTime>
#include <qfile.h>

#include "appTranslate.h"
#include "jsonFileKey.h"
#include "musicDecoder.h"
#include "renderImage.h"

#include "../msgInfo/messageErrorOut.h"

#include "../systemTrayIcon/systemTrayIcon.h"

#include "../window/mainWindow.h"

#include "translate/systemTrayIconTranslate.h"
AppInstance *AppInstance::instance = nullptr;

AppInstance * AppInstance::getAppInstance( ) {
	return instance;
}

AppInstance::AppInstance( int &argc, char **argv, int app_flag_s ) : QApplication( argc, argv, app_flag_s ) {
}

void AppInstance::deleteResource( ) {
	#define d_r( ptr ) if(ptr) (delete ptr, ptr = nullptr )
	d_r( mainWindow );
	d_r( musicDecoder );
	d_r( jsonFileKey );
	d_r( translate );
	d_r( startDateTime );
	d_r( renderImage );
	d_r( systemTrayIcon );
	instance = nullptr;
}

AppInstance::~AppInstance( ) {
	deleteResource( );
}

bool AppInstance::notify( QObject *object, QEvent *event ) {
	if( object == mainWindow ) {
		auto type = event->type( );
		switch( type ) {
			case QEvent::Type::Close :
				mainWindow->writeWidgetSettingToFile( );
				break;
		}
	}
	return QApplication::notify( object, event );
}

bool AppInstance::init( ) {
	deleteResource( );
	// 自身数据初始化先，再到子对象初始化
	appSettingPath = applicationDirPath( );

	instance = this;
	startDateTime = new QDateTime( QDateTime::currentDateTime( ) );
	translate = new AppTranslate;
	jsonFileKey = new JsonFileKey;
	musicDecoder = new MusicDecoder;
	mainWindow = new MainWindow;
	systemTrayIcon = new SystemTrayIcon;
	renderImage = new RenderImage;
	if( translate->init( ) == false )
		return false;
	if( jsonFileKey->init( ) == false )
		return false;
	if( musicDecoder->init( ) == false )
		return false;
	if( renderImage->init( ) == false )
		return false;
	if( mainWindow->init( ) == false )
		return false;
	// 托盘可能会初始化失败，它的可选的，需要时可
	if( systemTrayIcon->init( ) == false )
		Message_Error_Out << translate->getSystemTrayIcon( )->getIsSystemTrayAvailableError( );

	return true;
}

int AppInstance::run( ) {
	mainWindow->show( );

	exitCode = exec( );

	return exitCode;
}

const QDateTime * AppInstance::getStartDateTime( ) const {
	return startDateTime;
}

const JsonFileKey * AppInstance::getJsonFileKey( ) const {
	return jsonFileKey;
}

const AppTranslate * AppInstance::getTranslate( ) const {
	return translate;
}

MusicDecoder * AppInstance::getMusicDecoder( ) const {
	return musicDecoder;
}

int AppInstance::getExitCode( ) const {
	return exitCode;
}

const RenderImage * AppInstance::getRenderImage( ) const {
	return renderImage;
}

QString AppInstance::getAppSettingPath( ) const {
	return appSettingPath;
}

bool AppInstance::showMainWindow( ) const {
	if( mainWindow == nullptr )
		return false;
	mainWindow->show( );
	mainWindow->raise( );
	mainWindow->activateWindow( );
	return true;
}

bool AppInstance::hideMainWindow( ) const {
	if( mainWindow == nullptr )
		return false;
	mainWindow->hide( );
	return true;
}

MainWindow * AppInstance::getMainWindow( ) const {
	return mainWindow;
}
