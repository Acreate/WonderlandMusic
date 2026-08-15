#include "appDateTimerManage.h"

#include <QDateTime>

#include "../../head/release_macro.h"

bool AppDateTimerManage::init( ) {
	return true;
}

bool AppDateTimerManage::initBefore( ) {
	deleteResource( );
	startDateTime = new QDateTime( QDateTime::currentDateTime( ) );
	return true;
}

bool AppDateTimerManage::initAfter( ) {
	return true;
}

bool AppDateTimerManage::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( startDateTime );
	return true;
}

AppDateTimerManage::~AppDateTimerManage( ) {
	deleteResource( );
}

const QDateTime * AppDateTimerManage::getStartDateTime( ) const {
	return startDateTime;
}
