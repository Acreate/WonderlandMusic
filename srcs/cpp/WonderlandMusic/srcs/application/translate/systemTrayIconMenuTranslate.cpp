#include "systemTrayIconMenuTranslate.h"

#include <application/appTranslate.h>
#include <head/defininition_get_translate.h>
#include <tools/instanceTools.h>

Defininition_Get_Translate( SystemTrayIconMenu );

bool SystemTrayIconMenuTranslate::init( ) {
	showMainMenu = QObject::tr( "显示窗口" );
	quitApp = QObject::tr( "退出程序" );
	return true;
}

const QString & SystemTrayIconMenuTranslate::getShowMainMenu( ) const {
	return showMainMenu;
}

const QString & SystemTrayIconMenuTranslate::getQuitApp( ) const {
	return quitApp;
}
