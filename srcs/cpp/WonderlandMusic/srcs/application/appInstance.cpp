#include "appInstance.h"

#include <QDateTime>

#include "appTranslate.h"
#include "jsonFileKey.h"
#include "musicDecoder.h"

#include "../window/mainWindow.h"
AppInstance *AppInstance::instance = nullptr;
AppInstance * AppInstance::getAppInstance( ) {
	return instance;
}
AppInstance::AppInstance( int &argc, char **argv, int app_flag_s ) : QApplication( argc, argv, app_flag_s ) {
	startDateTime = new QDateTime( QDateTime::currentDateTime( ) );
	translate = new AppTranslate;
	jsonFileKey = new JsonFileKey;
	musicDecoder = new MusicDecoder;
	instance = this;
}
AppInstance::~AppInstance( ) {
	delete musicDecoder;
	delete jsonFileKey;
	delete translate;
	delete startDateTime;
}
bool AppInstance::init( ) {
	if( translate->init( ) == false )
		return false;
	if( musicDecoder->init( ) == false )
		return false;
	if( jsonFileKey->init( ) == false )
		return false;
	return true;
}
int AppInstance::run( ) {

	MainWindow *mainWindow = new MainWindow;

	if( mainWindow->init( ) == false ) {
		delete mainWindow;
		exitCode = 1;
		return 1;
	}

	mainWindow->show( );

	exitCode = exec( );

	delete mainWindow;
	return exitCode;
}
