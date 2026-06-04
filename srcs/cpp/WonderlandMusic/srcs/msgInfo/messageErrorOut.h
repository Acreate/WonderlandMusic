#ifndef MESSAGEERROROUT_H_H_HEAD__FILE__
#define MESSAGEERROROUT_H_H_HEAD__FILE__
#include <qstring.h>
#include <source_location>

#include "../tools/dateTimeFormat.h"

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
	/// @brief 日期格式化对象
	DateTimeFormat dateTimeFormat;
public:
	MessageErrorOut( const QString &log_home_path = "log", const std::source_location &source_location = std::source_location::current( ) );
	MessageErrorOut & operator<<( const QString &msg );
	virtual ~MessageErrorOut( );
private:
	virtual QString & formatMessageOut( QString &result_msg, const std::source_location &source_location, const QString &msg ) const;
};

#endif // MESSAGEERROROUT_H_H_HEAD__FILE__
