#ifndef MESSAGEERROROUT_H_H_HEAD__FILE__
#define MESSAGEERROROUT_H_H_HEAD__FILE__
#include <qstring.h>
#include <source_location>

/// @brief 临时创建一个 MessageErrorOut 对象
#define Message_Error_Out MessageErrorOut()

class DateTimeFormat;
class QDate;
class MessageErrorOut {
	std::vector< QString > outMsgVector;
	std::source_location location;
	QString logHomePtah;
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
	} translate;
	bool isWriteFile;
public:
	MessageErrorOut( bool is_write_file = true, const QString &log_home_path = "log", const std::source_location &source_location = std::source_location::current( ) );
	MessageErrorOut & operator<<( const QString &msg );
	MessageErrorOut & operator<<( const QStringList &msg );
	virtual ~MessageErrorOut( );
private:
	virtual QString & formatMessageOut( const DateTimeFormat &date_time_format, QString &result_msg, const std::source_location &source_location, const QString &msg ) const;
};

#endif // MESSAGEERROROUT_H_H_HEAD__FILE__
