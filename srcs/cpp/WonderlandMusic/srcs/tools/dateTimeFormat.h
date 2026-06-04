#ifndef DATETIMEFORMAT_H_H_HEAD__FILE__
#define DATETIMEFORMAT_H_H_HEAD__FILE__

#include <qdatetime.h>
#include <qstring.h>

class QDateTime;
class QTime;
class QDate;
class DateTimeFormat {
	class Translate {
		friend class DateTimeFormat;
		/// @brief 年
		QString year;
		/// @brief 月
		QString month;
		/// @brief 日
		QString day;
		/// @brief 小时
		QString hour;
		/// @brief 分钟
		QString minute;
		/// @brief 秒
		QString second;
		/// @brief 毫秒
		QString millsecond;
	public:
		virtual ~Translate( ) = default;
		Translate( );
		virtual const QString & getYear( ) const { return year; }
		virtual const QString & getMonth( ) const { return month; }
		virtual const QString & getDay( ) const { return day; }
		virtual const QString & getHour( ) const { return hour; }
		virtual const QString & getMinute( ) const { return minute; }
		virtual const QString & getSecond( ) const { return second; }
		virtual const QString & getMillsecond( ) const { return millsecond; }
	};
	Translate translate;
	QDate currentDate;
	QTime currentTime;
private:
	virtual void fillData( const QChar *source_data, const qsizetype &source_count, QChar *dest_data ) const;
public:
	virtual ~DateTimeFormat( ) = default;
	DateTimeFormat( const QDate &current_date, const QTime &current_time );
	DateTimeFormat( const QDateTime &current_date_time );
	DateTimeFormat( );

	virtual QString & formatData( QString &result_format, const QDate &format_data ) const;
	virtual QString & formatTime( QString &result_format, const QTime &format_time ) const;
	virtual QString formatData( const QDate &format_data ) const {
		QString result;
		return formatData( result, format_data );
	}
	virtual QString formatTime( const QTime &format_time ) const {
		QString result;
		return formatTime( result, format_time );
	}
	virtual QString & formatData( QString &result_format ) const {
		return formatData( result_format, this->currentDate );
	}
	virtual QString & formatTime( QString &result_format ) const {
		return formatTime( result_format, this->currentTime );
	}
	virtual QString formatData( ) const {
		QString result;
		return formatData( result );
	}
	virtual QString formatTime( ) const {
		QString result;
		return formatTime( result );
	}
};

#endif // DATETIMEFORMAT_H_H_HEAD__FILE__
