#include "mainWindowTranslate.h"

#include <application/appTranslate.h>
#include <head/defininition_get_translate.h>
#include <tools/instanceTools.h>

Defininition_Get_Translate( MainWindow );

bool MainWindowTranslate::init( ) {
	appWindowTitleName = QObject::tr( "仙村音乐" );
	return true;
}

const QString & MainWindowTranslate::getAppWindowTitleName( ) const {
	return appWindowTitleName;
}
