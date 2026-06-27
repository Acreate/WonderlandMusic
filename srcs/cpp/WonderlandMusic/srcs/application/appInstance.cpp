#include "appInstance.h"

#include <QJsonObject>
#include <qfile.h>
#include <qtranslator.h>

#include "appTranslate.h"
#include "jsonFileKey.h"
#include "musicDecoder.h"
#include "renderImage.h"

#include "../msgInfo/messageErrorOut.h"

#include "../systemTrayIcon/systemTrayIcon.h"

#include "../tools/pathTools.h"

#include "../window/mainWindow.h"

#include "translate/systemTrayIconTranslate.h"
AppInstance *AppInstance::instance = nullptr;

bool AppInstance::initVar( ) {
	QString dirPath = applicationDirPath( );
	appSettingPath = PathTools::getAutoShortenPathName( dirPath ) + "/program/";

	constAppSettingPath = appSettingPath + "/json/AppInstance.json";
	constAppDefaultTranslatePath = appSettingPath + "/translations/WonderlandMusic.qm";
	constAppIniDirHomePathJsonKey = "app.ini.dir.home.path";

	instance = this;
	// 创建变量
	startDateTime = new QDateTime( QDateTime::currentDateTime( ) );
	translate = new AppTranslate;
	jsonFileKey = new JsonFileKey;
	musicDecoder = new MusicDecoder;
	mainWindow = new MainWindow;
	systemTrayIcon = new SystemTrayIcon;
	renderImage = new RenderImage;
	appTranslator = new QTranslator;
	return true;
}

bool AppInstance::initReadJson( ) {
	QJsonObject appJsonObject;
	if( PathTools::readJsonObject( appJsonObject, constAppSettingPath ) == false )
		return true;
	auto end = appJsonObject.end( );
	auto find = appJsonObject.find( constAppIniDirHomePathJsonKey );
	if( end != find ) {
		auto string = find.value( ).toString( );
		appSettingPath = PathTools::getAutoShortenPathName( string );
	}
	return true;
}

bool AppInstance::writeJson( ) {
	QJsonObject appJsonObject;
	appJsonObject.insert( constAppIniDirHomePathJsonKey, PathTools::getAutoShortenPathName( appSettingPath ) );
	PathTools::writeJsonObject( appJsonObject, constAppSettingPath );
	return true;
}

bool AppInstance::initTranslate( ) {
	if( setAppStringTranslate( constAppDefaultTranslatePath ) == false )
		return false;

	return true;
}

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
	if( appTranslator ) {
		removeTranslator( appTranslator );
		delete appTranslator;
		appTranslator = nullptr;
	}
	instance = nullptr;
}

AppInstance::~AppInstance( ) {
	writeJson( );
	deleteResource( );
}

bool AppInstance::notify( QObject *object, QEvent *event ) {
	if( object == mainWindow ) {
		auto type = event->type( );
		switch( type ) {
			case QEvent::Type::Close :
				mainWindow->writeWidgetSettingToFile( );
				if( QSystemTrayIcon::isSystemTrayAvailable( ) == false )
					quit( ); // 如果不支持托盘，隐藏则退出
				break;
		}
	}
	return QApplication::notify( object, event );
}

bool AppInstance::init( ) {
	deleteResource( );
	// 自身数据初始化先，再到子对象初始化
	if( initVar( ) == false )
		return false;
	// 读取配置文件
	if( initReadJson( ) == false )
		return false;
	// 初始化翻译文件
	if( initTranslate( ) == false )
		return false;

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

void AppInstance::setAppSettingPath( const QString &app_setting_dir_home_path ) {
	appSettingPath = PathTools::getAutoShortenPathName( app_setting_dir_home_path );
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

bool AppInstance::setAppStringTranslate( const QString &translate_file_path ) {
	QFileInfo info( translate_file_path );
	if( info.exists( ) == false )
		return false;
	QTranslator *newTranslator = new QTranslator;
	if( newTranslator->load( info.absoluteFilePath( ) ) == false ) {
		delete newTranslator;
		return false;
	}
	if( appTranslator ) {
		removeTranslator( appTranslator );
		delete appTranslator;
	}
	appTranslator = newTranslator;
	installTranslator( appTranslator );
	return true;
}
