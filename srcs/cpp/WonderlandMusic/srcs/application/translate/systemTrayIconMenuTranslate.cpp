#include "systemTrayIconMenuTranslate.h"

#include <QObject>

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
