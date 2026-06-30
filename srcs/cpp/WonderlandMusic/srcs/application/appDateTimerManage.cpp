#include "appDateTimerManage.h"

#include <QDateTime>

#include "../tools/templateArgs.h"

bool AppDateTimerManage::init( ) {
	deleteResource( );
	if( TemplateArgs::make_args_ptr( startDateTime, QDateTime::currentDateTime( ) ) == nullptr )
		return false;
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
