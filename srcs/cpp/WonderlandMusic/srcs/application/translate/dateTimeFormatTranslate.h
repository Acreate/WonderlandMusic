#ifndef DATETIMEFORMATTRANSLATE_H_H_HEAD__FILE__
#define DATETIMEFORMATTRANSLATE_H_H_HEAD__FILE__
#include "iTranslate.h"

class DateTimeFormatTranslate : public ITranslate {
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
	bool init( ) override;

public:
	virtual const QString & getYear( ) const;

	virtual const QString & getMonth( ) const;

	virtual const QString & getDay( ) const;

	virtual const QString & getHour( ) const;

	virtual const QString & getMinute( ) const;

	virtual const QString & getSecond( ) const;

	virtual const QString & getMillsecond( ) const;
};

#endif // DATETIMEFORMATTRANSLATE_H_H_HEAD__FILE__
