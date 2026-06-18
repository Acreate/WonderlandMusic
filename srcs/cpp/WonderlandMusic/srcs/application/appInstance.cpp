#include "appInstance.h"

#include <QDateTime>

#include "appTranslate.h"
#include "jsonFileKey.h"
#include "musicDecoder.h"
#include "renderImage.h"

#include "../window/mainWindow.h"
AppInstance *AppInstance::instance = nullptr;

AppInstance * AppInstance::getAppInstance( ) {
	return instance;
}

AppInstance::AppInstance( int &argc, char **argv, int app_flag_s ) : QApplication( argc, argv, app_flag_s ) {
	instance = this;
	startDateTime = new QDateTime( QDateTime::currentDateTime( ) );
	translate = new AppTranslate;
	jsonFileKey = new JsonFileKey;
	musicDecoder = new MusicDecoder;
	mainWindow = new MainWindow;
	renderImage = new RenderImage;
}

AppInstance::~AppInstance( ) {
	delete mainWindow;
	delete musicDecoder;
	delete jsonFileKey;
	delete translate;
	delete startDateTime;
	delete renderImage;
}

bool AppInstance::init( ) {
	// 自身数据初始化先，再到子对象初始化
	appSettingPath = applicationDirPath( );

	if( translate->init( ) == false )
		return false;
	if( musicDecoder->init( ) == false )
		return false;
	if( jsonFileKey->init( ) == false )
		return false;
	if( renderImage->init( ) == false )
		return false;
	if( mainWindow->init( ) == false )
		return false;
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
