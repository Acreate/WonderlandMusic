#include "mainWindowTranslate.h"

bool MainWindowTranslate::init( ) {
	appWindowTitleName = QObject::tr( "仙村音乐" );
	return true;
}

const QString & MainWindowTranslate::getAppWindowTitleName( ) const {
	return appWindowTitleName;
}
