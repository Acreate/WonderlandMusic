#ifndef SOURCELOCATIONTOOLS_H_H_HEAD__FILE__
#define SOURCELOCATIONTOOLS_H_H_HEAD__FILE__

class QString;

namespace std {
	struct source_location;
}

namespace SourceLocationTools {
	/// @brief 格式化输出对象
	/// @param format_string 格式化信息输出
	/// @param source_file 格式化源文件路径
	/// @param source_function 格式化源文件函数
	/// @param source_line 格式化源文件行号
	/// @param location 被格式化的源文件信号对象
	/// @param msg 格式化的消息
	void formatString( QString &format_string, QString &source_file, QString &source_function, QString &source_line, const std::source_location &location, const QString &msg );
	/// @brief 格式化一个源文件信息对象
	/// @param source_file 格式化源文件路径
	/// @param source_function 格式化源文件函数
	/// @param source_line 格式化源文件行号
	/// @param location 被格式化的源文件信号对象
	void formatSourceFilePath( QString &source_file, QString &source_function, QString &source_line, const std::source_location &location );
};

#endif // SOURCELOCATIONTOOLS_H_H_HEAD__FILE__
