#ifndef SOURCELOCATIONTOOLS_H_H_HEAD__FILE__
#define SOURCELOCATIONTOOLS_H_H_HEAD__FILE__

class QString;

namespace std {
	struct source_location;
}

namespace SourceLocationTools {
	void formatString( QString &format_string, QString &source_file, QString &source_function, QString &source_line, const std::source_location &location, const QString &msg );
	void formatSourceFilePath( QString &source_file, QString &source_function, QString &source_line, const std::source_location &location );
};

#endif // SOURCELOCATIONTOOLS_H_H_HEAD__FILE__
