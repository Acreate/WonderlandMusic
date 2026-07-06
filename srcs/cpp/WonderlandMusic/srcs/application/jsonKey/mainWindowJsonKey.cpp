#include "mainWindowJsonKey.h"

#include "../appDataManage.h"
#include "../appInstance.h"

bool MainWindowJsonKey::init( ) {
	objectName = "app.main.window";
	pointXPos = "point.x";
	pointYPos = "point.y";
	sizeWidth = "size.w";
	sizeHeight = "size.h";
	return true;
}

const QString & MainWindowJsonKey::getPointXPos( ) const {
	return pointXPos;
}

const QString & MainWindowJsonKey::getPointYPos( ) const {
	return pointYPos;
}

const QString & MainWindowJsonKey::getSizeWidth( ) const {
	return sizeWidth;
}

const QString & MainWindowJsonKey::getSizeHeight( ) const {
	return sizeHeight;
}

const QString & MainWindowJsonKey::getObjectName( ) const {
	return objectName;
}
