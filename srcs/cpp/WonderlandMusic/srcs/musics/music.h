#ifndef MUSIC_H_H_HEAD__FILE__
#define MUSIC_H_H_HEAD__FILE__
#include <QString>

class QImage;
class QDateTime;
/// @brief 音乐类
class Music {
private:
	/// @brief 音乐文件路径
	QString musicPath;
	/// @brief 音乐名称
	QString musicName;
	/// @brief 歌手
	QString singer;
	/// @brief 时长（毫秒）
	qint64 duration_ms;
public:
	virtual ~Music( );
	Music( const QString &music_path );
	virtual const QString & getMusicPath( ) const { return musicPath; }
	virtual const QString & getMusicPath1( ) const { return musicPath; }
	virtual const QString & getMusicName( ) const { return musicName; }
	virtual const QString & getSinger( ) const { return singer; }
	virtual qint64 getDurationMs( ) const { return duration_ms; }
};

#endif // MUSIC_H_H_HEAD__FILE__
