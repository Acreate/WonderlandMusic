#include "aboutWidgetJsonKey.h"

#include "../../tools/pathInfoTools.h"

bool AboutWidgetJsonKey::init( ) {
	qtLogoIconPath = "/png/qtlogo-64.png";
	return true;
}

QString AboutWidgetJsonKey::getQtLogoIconPath( ) const {
	QString applicationDirPath;
	if( PathInfoTools::getAppSettintHomePath( applicationDirPath ) )
		return applicationDirPath + qtLogoIconPath;
	return qtLogoIconPath;
}
