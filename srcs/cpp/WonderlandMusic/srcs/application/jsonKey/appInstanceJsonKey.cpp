#include "appInstanceJsonKey.h"

bool AppInstanceJsonKey::init( ) {
	appIniHomeDirPath = "app.ini.dir.home.path";
	return true;
}

const QString & AppInstanceJsonKey::getAppIniHomeDirPath( ) const {
	return appIniHomeDirPath;
}
