#ifndef PATHTOOLS_H_H_HEAD__FILE__
#define PATHTOOLS_H_H_HEAD__FILE__

#include <QDir>
#include <QFileInfo>
class QString;

class PathTools {
public:
	static bool entryList( QStringList &result_get_path, const QString &entry_path, bool foreach_in_dir_path, QDir::Filters filters );

	static bool entryList( QStringList &result_get_path, const QString &entry_path, bool foreach_in_dir_path );

	static bool entryList( QStringList &result_get_path, const QString &entry_path, QDir::Filters filters, QDir::SortFlags sort );

	static bool entryList( QStringList &result_get_path, const QString &entry_path, QDir::Filters filters );

	static bool entryList( QStringList &result_get_path, const QString &entry_path );

	static bool entryList( QStringList &result_get_path, const QStringList &entry_path, bool foreach_in_dir_path, QDir::Filters filters );

	static bool entryList( QStringList &result_get_path, const QStringList &entry_path, bool foreach_in_dir_path );

	static bool entryList( QStringList &result_get_path, const QStringList &entry_path, QDir::Filters filters );

	static bool entryList( QStringList &result_get_path, const QStringList &entry_path );

	static bool entryList( QStringList &result_get_path, const std::vector< QString > &entry_path, bool foreach_in_dir_path, QDir::Filters filters );

	static bool entryList( QStringList &result_get_path, const std::vector< QString > &entry_path, bool foreach_in_dir_path );

	static bool entryList( QStringList &result_get_path, const std::vector< QString > &entry_path, QDir::Filters filters );

	static bool entryList( QStringList &result_get_path, const std::vector< QString > &entry_path );

	static qsizetype filterFile( QStringList &result_get_path, const QStringList &entry_path );

	static qsizetype filterDir( QStringList &result_get_path, const QStringList &entry_path );

	static qsizetype filterMusicFile( QStringList &result_get_path, const QStringList &entry_path );

	static qsizetype filterFile( QStringList &result_get_path, const std::vector< QString > &entry_path );

	static qsizetype filterDir( QStringList &result_get_path, const std::vector< QString > &entry_path );

	static qsizetype filterMusicFile( QStringList &result_get_path, const std::vector< QString > &entry_path );

	static bool readJsonObject( QJsonObject &result_json_object, const QString &json_file_path );

	static bool writeJsonObject( const QJsonObject &result_json_object, const QString &json_file_path );
};

#endif // PATHTOOLS_H_H_HEAD__FILE__
