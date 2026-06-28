#include "appDateTimerManage.h"

#include <QDateTime>

#include "../tools/templateArgs.h"

bool AppDateTimerManage::init( ) {
	deleteResource( );
	if( TemplateArgs::make_ptr( startDateTime, QDateTime::currentDateTime( ) ) == nullptr )
		return false;
	return true;
}

bool AppDateTimerManage::deleteResource( ) {
	if( TemplateArgs::delete_ptr( startDateTime ) == false )
		return false;
	return true;
}

AppDateTimerManage::~AppDateTimerManage( ) {
	deleteResource( );
}

const QDateTime * AppDateTimerManage::getStartDateTime( ) const {
	return startDateTime;
}
