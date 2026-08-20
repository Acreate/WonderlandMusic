#include "systemTrayIconJsonKey.h"

bool SystemTrayIconJsonKey::init( ) {
	iconFilePath = "/png/qtlogo-64.png";
	return true;
}

QString SystemTrayIconJsonKey::getIconFilePath( ) const {
	return getNormalJsonKeyFile( iconFilePath );
}
