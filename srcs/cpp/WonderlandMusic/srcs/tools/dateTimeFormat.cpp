#include "dateTimeFormat.h"

#include <QObject>
#include <qdatetime.h>
DateTimeFormat::Translate::Translate( ) {
	year = QObject::tr( "年" );
	month = QObject::tr( "月" );
	day = QObject::tr( "日" );
	hour = QObject::tr( "时" );
	minute = QObject::tr( "分" );
	second = QObject::tr( "秒" );
	millsecond = QObject::tr( "毫秒" );
}
void DateTimeFormat::fillData( const QChar *source_data, const qsizetype &source_count, QChar *dest_data ) const {
	qsizetype index = 0;
	for( ; index < source_count; ++index )
		dest_data[ index ] = source_data[ index ];
}
DateTimeFormat::DateTimeFormat( const QDate &current_date, const QTime &current_time ) {
	currentDate = current_date;
	currentTime = current_time;
}
DateTimeFormat::DateTimeFormat( const QDateTime &current_date_time ) {
	currentDate = current_date_time.date( );
	currentTime = current_date_time.time( );
}
DateTimeFormat::DateTimeFormat( ) {
	auto current = QDateTime::currentDateTime( );
	currentDate = current.date( );
	currentTime = current.time( );
}
QString & DateTimeFormat::formatData( QString &result_format, const QDate &format_data ) const {
	// 测量年翻译的长度
	qsizetype translateYearLenght = translate.year.length( );
	// 测量月翻译的长度
	qsizetype translateMonthLenght = translate.month.length( );
	// 测量日翻译的长度
	qsizetype translateDayLenght = translate.day.length( );
	// 年份转字符串
	auto yearDataToString = QString( "%1" ).arg( QString::number( format_data.year( ) ), 4, '0' );
	// 月份转字符串
	auto monthDataToString = QString( "%1" ).arg( QString::number( format_data.month( ) ), 2, '0' );
	// 日期转字符串
	auto dayDataToString = QString( "%1" ).arg( QString::number( format_data.day( ) ), 2, '0' );
	// 年数字长度
	qsizetype yearDataToStringLenght = yearDataToString.length( );
	// 月数字长度
	qsizetype monthDataToStringLenght = monthDataToString.length( );
	// 日数字长度
	qsizetype dayDataToStringLenght = dayDataToString.length( );
	// 新的大小
	qsizetype resetMaxSize = yearDataToStringLenght + monthDataToStringLenght + dayDataToStringLenght + translateYearLenght + translateMonthLenght + translateDayLenght;
	// 重置字符串大小
	result_format.resize( resetMaxSize );
	// 填充计数
	qsizetype fillIndex;
	// 获取目标地址
	QChar *destData = result_format.data( );

	// 填充年份数字
	fillData( yearDataToString.data( ), yearDataToStringLenght, destData );
	// 填充年翻译
	fillIndex = yearDataToStringLenght;
	fillData( translate.year.data( ), translateYearLenght, destData + fillIndex );

	// 填充月份数字
	fillIndex = fillIndex + translateYearLenght;
	fillData( monthDataToString.data( ), monthDataToStringLenght, destData + fillIndex );
	// 填充月翻译
	fillIndex = fillIndex + monthDataToStringLenght;
	fillData( translate.month.data( ), translateMonthLenght, destData + fillIndex );

	// 填充日期数字
	fillIndex = fillIndex + translateMonthLenght;
	fillData( dayDataToString.data( ), dayDataToStringLenght, destData + fillIndex );
	// 填充日期翻译
	fillIndex = fillIndex + dayDataToStringLenght;
	fillData( translate.day.data( ), translateDayLenght, destData + fillIndex );

	return result_format;
}
QString & DateTimeFormat::formatTime( QString &result_format, const QTime &format_time ) const {
	// 测量时翻译的长度
	qsizetype translateHourLenght = translate.hour.length( );
	// 测量分翻译的长度
	qsizetype translateMinuteLenght = translate.minute.length( );
	// 测量秒翻译的长度
	qsizetype translateSecondLenght = translate.second.length( );
	// 测量毫秒翻译的长度
	qsizetype translateMillsecondLenght = translate.millsecond.length( );

	// 小时转字符串
	auto hourTimeToString = QString( "%1" ).arg( QString::number( format_time.hour( ) ), 2, '0' );
	// 分钟转字符串
	auto minuteTimeToString = QString( "%1" ).arg( QString::number( format_time.minute( ) ), 2, '0' );
	// 秒数转字符串
	auto secondTimeToString = QString( "%1" ).arg( QString::number( format_time.second( ) ), 2, '0' );
	// 毫秒转字符串
	auto millsecondTimeToString = QString( "%1" ).arg( QString::number( format_time.msec( ) ), 3, '0' );

	// 小时数字长度
	qsizetype hourTimeToStringLenght = hourTimeToString.length( );
	// 分钟数字长度
	qsizetype minuteTimeToStringLenght = minuteTimeToString.length( );
	// 秒数数字长度
	qsizetype secondTimeToStringLenght = secondTimeToString.length( );
	// 毫秒数字长度
	qsizetype millsecondTimeToStringLenght = millsecondTimeToString.length( );

	// 新的大小
	qsizetype resetMaxSize = hourTimeToStringLenght + minuteTimeToStringLenght + secondTimeToStringLenght + millsecondTimeToStringLenght + translateHourLenght + translateMinuteLenght + translateSecondLenght + translateMillsecondLenght;
	result_format.resize( resetMaxSize );

	// 重置字符串大小
	result_format.resize( resetMaxSize );
	// 填充计数
	qsizetype fillIndex;
	// 获取目标地址
	QChar *destData = result_format.data( );

	// 填充小时数字
	fillData( hourTimeToString.data( ), hourTimeToStringLenght, destData );
	// 填充小时翻译
	fillIndex = hourTimeToStringLenght;
	fillData( translate.hour.data( ), translateHourLenght, destData + fillIndex );

	// 填充分钟数字
	fillIndex = fillIndex + translateHourLenght;
	fillData( minuteTimeToString.data( ), minuteTimeToStringLenght, destData + fillIndex );
	// 填充分钟翻译
	fillIndex = fillIndex + minuteTimeToStringLenght;
	fillData( translate.minute.data( ), translateMinuteLenght, destData + fillIndex );

	// 填充秒数数字
	fillIndex = fillIndex + translateMinuteLenght;
	fillData( secondTimeToString.data( ), secondTimeToStringLenght, destData + fillIndex );
	// 填充秒数翻译
	fillIndex = fillIndex + secondTimeToStringLenght;
	fillData( translate.second.data( ), translateSecondLenght, destData + fillIndex );

	// 填充秒数数字
	fillIndex = fillIndex + translateSecondLenght;
	fillData( millsecondTimeToString.data( ), millsecondTimeToStringLenght, destData + fillIndex );
	// 填充秒数翻译
	fillIndex = fillIndex + millsecondTimeToStringLenght;
	fillData( translate.millsecond.data( ), translateMillsecondLenght, destData + fillIndex );

	return result_format;
}
