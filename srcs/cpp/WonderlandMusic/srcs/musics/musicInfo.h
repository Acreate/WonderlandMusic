#ifndef MUSICINFO_H_H_HEAD__FILE__
#define MUSICINFO_H_H_HEAD__FILE__
#include <QUrl>

class MusicInfo {
protected:
	/// @brief 音乐文件路径
	QUrl musicUrl;
	/// @brief 音乐名称
	QString musicName;
	/// @brief 歌手
	QString singer;
	/// @brief 时长（毫秒）
	qint64 duration_ms;
public:
	virtual ~MusicInfo() = default;
	MusicInfo( ) { }
	virtual bool open( const QString &file_path );
	virtual const QUrl & getMusicUrl( ) const { return musicUrl; }
	virtual const QString & getMusicName( ) const { return musicName; }
	virtual const QString & getSinger( ) const { return singer; }
	virtual qint64 getDurationMs( ) const { return duration_ms; }
};

#endif // MUSICINFO_H_H_HEAD__FILE__
