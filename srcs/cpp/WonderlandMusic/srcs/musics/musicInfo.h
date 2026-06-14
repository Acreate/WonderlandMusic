#ifndef MUSICINFO_H_H_HEAD__FILE__
#define MUSICINFO_H_H_HEAD__FILE__
#include <qstring.h>

class QLabel;
class QMediaMetaData;
class QMediaPlayer;
class MusicInfo {
protected:
	/// @brief 音乐文件路径
	QString filePath;
	/// @brief 音乐名称
	QString musicName;
	/// @brief 歌手
	QString singer;
	/// @brief 时长（毫秒）
	qint64 durationMs;
public:
	virtual ~MusicInfo( ) { }
	MusicInfo( const QString &file_path, const QString &music_name, const QString &singer, qint64 duration_ms )
		: filePath( file_path ),
		musicName( music_name ),
		singer( singer ),
		durationMs( duration_ms ) { }
	MusicInfo( const MusicInfo &other )
		: filePath { other.filePath },
		musicName { other.musicName },
		singer { other.singer },
		durationMs { other.durationMs } { }
	MusicInfo & operator=( const MusicInfo &other ) {
		if( this == &other )
			return *this;
		filePath = other.filePath;
		musicName = other.musicName;
		singer = other.singer;
		durationMs = other.durationMs;
		return *this;
	}
	virtual const QString & getFilePath( ) const { return filePath; }
	virtual const QString & getMusicName( ) const { return musicName; }
	virtual const QString & getSinger( ) const { return singer; }
	virtual qint64 getDurationMs( ) const { return durationMs; }
};

#endif // MUSICINFO_H_H_HEAD__FILE__
