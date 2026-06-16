#ifndef DATETIMEFORMAT_H_H_HEAD__FILE__
#define DATETIMEFORMAT_H_H_HEAD__FILE__

#include <qdatetime.h>
#include <qstring.h>

class QDateTime;
class QTime;
class QDate;
class DateTimeFormat {
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
public:
	static QString millsecondToHourMinSecFrom( qint64 totalMs );
};

#endif // DATETIMEFORMAT_H_H_HEAD__FILE__
