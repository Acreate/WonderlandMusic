#ifndef STRINGTOOLS_H_H_HEAD__FILE__
#define STRINGTOOLS_H_H_HEAD__FILE__
#include <qtypes.h>

class QString;

namespace StringTools {
	/// @brief 返回文件的后缀名
	/// @param file_name 文件
	/// @return 匹配后缀位
	QString getFileSuffix( const QString &file_name );
}

#endif // STRINGTOOLS_H_H_HEAD__FILE__
