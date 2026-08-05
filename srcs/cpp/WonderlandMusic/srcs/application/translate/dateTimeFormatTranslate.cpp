#include "dateTimeFormatTranslate.h"

#include <application/appTranslate.h>
#include <head/defininition_get_translate.h>
#include <tools/instanceTools.h>

Defininition_Get_Translate( DateTimeFormat );

bool DateTimeFormatTranslate::init( ) {
	year = QObject::tr( "年" );
	month = QObject::tr( "月" );
	day = QObject::tr( "日" );
	hour = QObject::tr( "时" );
	minute = QObject::tr( "分" );
	second = QObject::tr( "秒" );
	millsecond = QObject::tr( "毫秒" );

	return true;
}

const QString & DateTimeFormatTranslate::getYear( ) const {
	return year;
}

const QString & DateTimeFormatTranslate::getMonth( ) const {
	return month;
}

const QString & DateTimeFormatTranslate::getDay( ) const {
	return day;
}

const QString & DateTimeFormatTranslate::getHour( ) const {
	return hour;
}

const QString & DateTimeFormatTranslate::getMinute( ) const {
	return minute;
}

const QString & DateTimeFormatTranslate::getSecond( ) const {
	return second;
}

const QString & DateTimeFormatTranslate::getMillsecond( ) const {
	return millsecond;
}
