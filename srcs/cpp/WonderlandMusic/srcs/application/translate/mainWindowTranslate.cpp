#include "mainWindowTranslate.h"

#include <QObject>

bool MainWindowTranslate::init( ) {
	appWindowTitleName = QObject::tr( "仙村音乐" );
	return true;
}

const QString & MainWindowTranslate::getAppWindowTitleName( ) const {
	return appWindowTitleName;
}
