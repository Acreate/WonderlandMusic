#include "aboutWidgetJsonKey.h"

bool AboutWidgetJsonKey::init( ) {
	qtLogoIconPath = "/png/qtlogo-64.png";
	return true;
}

QString AboutWidgetJsonKey::getQtLogoIconPath( ) const {
	return getNormalJsonKeyFile( qtLogoIconPath );
}
