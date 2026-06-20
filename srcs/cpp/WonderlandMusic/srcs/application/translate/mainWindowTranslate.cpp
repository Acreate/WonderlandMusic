#include "mainWindowTranslate.h"

#include <QObject>

bool MainWindowTranslate::init( ) {
	appWindowTitleName = QObject::tr( "仙缘村落" );
	musicTypeName = QObject::tr( "音频" );
	settingWidget = QObject::tr( "软件设置" );
	aboutWidget = QObject::tr( "关于" );
	return true;
}

const QString & MainWindowTranslate::getAppWindowTitleName( ) const {
	return appWindowTitleName;
}

const QString & MainWindowTranslate::getSettingWidget( ) const {
	return settingWidget;
}

const QString & MainWindowTranslate::getAboutWidget( ) const {
	return aboutWidget;
}

const QString & MainWindowTranslate::getMusicTypeName( ) const {
	return musicTypeName;
}
