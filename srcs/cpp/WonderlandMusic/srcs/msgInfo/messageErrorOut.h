#ifndef MESSAGEERROROUT_H_H_HEAD__FILE__
#define MESSAGEERROROUT_H_H_HEAD__FILE__
#include <qstring.h>
#include <source_location>

/// @brief 临时创建一个 MessageErrorOut 对象
#define Message_Error_Out MessageErrorOut()

class DateTimeFormat;
class QDate;
class MessageErrorOut {
protected:
	class Translate {
		friend class MessageErrorOut;
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
	public:
		Translate( );
	};
protected:
	Translate translate;
	std::vector< QString > outMsgVector;
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
	MessageErrorOut & operator<<( const QString &msg );
	MessageErrorOut & operator<<( const QStringList &msg );
	MessageErrorOut & operator<<( const QChar &msg );
	MessageErrorOut & operator<<( const char &msg );
	MessageErrorOut & operator<<( const wchar_t &msg );
	MessageErrorOut & operator<<( const int64_t &msg );
	MessageErrorOut & operator<<( const int32_t &msg );
	MessageErrorOut & operator<<( const int16_t &msg );
	MessageErrorOut & operator<<( const uint64_t &msg );
	MessageErrorOut & operator<<( const uint32_t &msg );
	MessageErrorOut & operator<<( const uint16_t &msg );
	MessageErrorOut & operator<<( const uint8_t &msg );
	MessageErrorOut & operator<<( const void_ptr &msg );
	virtual const QString & getJoinString( ) const { return jointString; }
	virtual void setJoinString( const QString &join ) { this->jointString = join; }
	virtual const QString & getStartString( ) const { return startString; }
	virtual void setStartString( const QString &start_string ) { startString = start_string; }
	virtual const QString & getEndString( ) const { return endString; }
	virtual void setEndString( const QString &end_string ) { endString = end_string; }
private:
	virtual QString & formatMessageOut( const DateTimeFormat &date_time_format, QString &result_msg, const std::source_location &source_location, const QString &msg ) const;
};

#endif // MESSAGEERROROUT_H_H_HEAD__FILE__
