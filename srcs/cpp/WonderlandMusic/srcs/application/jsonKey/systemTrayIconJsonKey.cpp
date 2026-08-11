#include "systemTrayIconJsonKey.h"

#include "../../tools/pathInfoTools.h"

bool SystemTrayIconJsonKey::init( ) {
	iconFilePath = "/png/qtlogo-64.png";
	return true;
}

QString SystemTrayIconJsonKey::getIconFilePath( ) const {
	QString applicationDirPath;
	if( PathInfoTools::getAppSettintHomePath( applicationDirPath ) )
		return applicationDirPath + iconFilePath;
	return applicationDirPath + iconFilePath;
}
