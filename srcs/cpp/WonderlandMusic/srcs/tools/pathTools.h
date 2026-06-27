#ifndef PATHTOOLS_H_H_HEAD__FILE__
#define PATHTOOLS_H_H_HEAD__FILE__

#include <QAudioBuffer>
#include <QDir>

class QString;

namespace PathTools {
	bool entryList( QStringList &result_get_path, const QString &entry_path, bool foreach_in_dir_path, QDir::Filters filters );

	bool entryList( QStringList &result_get_path, const QString &entry_path, bool foreach_in_dir_path );

	bool entryList( QStringList &result_get_path, const QString &entry_path, QDir::Filters filters, QDir::SortFlags sort );

	bool entryList( QStringList &result_get_path, const QString &entry_path, QDir::Filters filters );

	bool entryList( QStringList &result_get_path, const QString &entry_path );

	bool entryList( QStringList &result_get_path, const QStringList &entry_path, bool foreach_in_dir_path, QDir::Filters filters );

	bool entryList( QStringList &result_get_path, const QStringList &entry_path, bool foreach_in_dir_path );

	bool entryList( QStringList &result_get_path, const QStringList &entry_path, QDir::Filters filters );

	bool entryList( QStringList &result_get_path, const QStringList &entry_path );

	bool entryList( QStringList &result_get_path, const std::vector< QString > &entry_path, bool foreach_in_dir_path, QDir::Filters filters );

	bool entryList( QStringList &result_get_path, const std::vector< QString > &entry_path, bool foreach_in_dir_path );

	bool entryList( QStringList &result_get_path, const std::vector< QString > &entry_path, QDir::Filters filters );

	bool entryList( QStringList &result_get_path, const std::vector< QString > &entry_path );

	qsizetype filterFile( QStringList &result_get_path, const QStringList &entry_path );

	qsizetype filterDir( QStringList &result_get_path, const QStringList &entry_path );

	qsizetype filterMusicFile( QStringList &result_get_path, const QStringList &entry_path );

	qsizetype filterFile( QStringList &result_get_path, const std::vector< QString > &entry_path );

	qsizetype filterDir( QStringList &result_get_path, const std::vector< QString > &entry_path );

	/// @brief 获取建议路径，如果在 app 路径下，则使用相对路径，如果不在，则使用绝对路径
	/// @param org_file_path 计算路径
	/// @return 建议路径
	QString getAutoShortenPathName( const QString &org_file_path );

	qsizetype filterMusicFile( QStringList &result_get_path, const std::vector< QString > &entry_path );

	bool readJsonObject( QJsonObject &result_json_object, const QString &json_file_path );

	bool writeJsonObject( const QJsonObject &result_json_object, const QString &json_file_path );

	bool wirteWavFile( const QString &wirte_file_path, const std::vector< char > &wirte_pcm_vector_data );

	bool wirteWavFile( const QString &wirte_file_path, const std::vector< QAudioBuffer > &wirte_pcm_vector_data );
}

#endif // PATHTOOLS_H_H_HEAD__FILE__
