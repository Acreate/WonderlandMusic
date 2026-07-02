#include "systemTrayIconTranslate.h"

#include <QObject>

bool SystemTrayIconTranslate::init( ) {
	isSystemTrayAvailableError = QObject::tr( "当前系统不支持托盘" );
	iconFileNotExists = QObject::tr( "当前托盘图标不存在" );
	iconLoadFileError = QObject::tr( "加载托盘图标失败" );
	appName = QObject::tr( "仙村音乐" );
	return true;
}

const QString & SystemTrayIconTranslate::getIsSystemTrayAvailableError( ) const {
	return isSystemTrayAvailableError;
}

const QString & SystemTrayIconTranslate::getIconFileNotExists( ) const {
	return iconFileNotExists;
}

const QString & SystemTrayIconTranslate::getIconLoadFileError( ) const {
	return iconLoadFileError;
}

const QString & SystemTrayIconTranslate::getAppName( ) const {
	return appName;
}
