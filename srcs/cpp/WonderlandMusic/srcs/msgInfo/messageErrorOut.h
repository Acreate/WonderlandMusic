#ifndef MESSAGEERROROUT_H_H_HEAD__FILE__
#define MESSAGEERROROUT_H_H_HEAD__FILE__
#include <qstring.h>
#include <source_location>

#include "messageString.h"

/// @brief 临时创建一个 MessageErrorOut 对象
#define Message_Error_Out MessageErrorOut()

class QDateTime;
class DateTimeFormat;
class QDate;

class MessageErrorOut {
protected:
	static std::shared_ptr< QDateTime > logStartDateTime;;

protected:
	/// @brief 源文件
	QString sourceFile;
	/// @brief 源文件函数
	QString sourceFunction;
	/// @brief 源文件行号
	QString sourceLine;
	/// @brief 创建目录错误
	QString createDirError;
	/// @brief 打开文件错误
	QString openFileError;

protected:
	std::vector< MessageString > outMsgVector;
	std::source_location location;
	QString logHomePtah;
	QString jointString;
	QString startString;
	QString endString;

	bool isWriteFile;

public:
	using void_ptr = void *;

public:
	virtual ~MessageErrorOut( );

	MessageErrorOut( bool is_write_file = true, const QString &log_home_path = "log", const std::source_location &source_location = std::source_location::current( ) );

	MessageErrorOut( const QString &log_home_path, const std::source_location &source_location );

	MessageErrorOut( const std::source_location &source_location );

	MessageErrorOut & operator<<( const MessageString &msg );

	virtual const QString & getJoinString( ) const;

	virtual void setJoinString( const QString &join );

	virtual const QString & getStartString( ) const;

	virtual void setStartString( const QString &start_string );

	virtual const QString & getEndString( ) const;

	virtual void setEndString( const QString &end_string );

	virtual const std::vector< MessageString > & getOutMsgVector( ) const;

	virtual QString toQString( ) const;

	virtual QString toQString( const DateTimeFormat &date_time_format ) const;

	virtual QString writeLog( const QString &wirte_log_path, const DateTimeFormat &date_time_format ) const;

	virtual QString writeLog( const DateTimeFormat &date_time_format ) const;

	virtual QString writeLog( const QString &wirte_log_path ) const;

	virtual QString writeLog( ) const;

private:
	virtual QString & formatMessageOut( const DateTimeFormat &date_time_format, QString &result_msg, const std::source_location &source_location, const QString &msg ) const;
};

#endif // MESSAGEERROROUT_H_H_HEAD__FILE__
