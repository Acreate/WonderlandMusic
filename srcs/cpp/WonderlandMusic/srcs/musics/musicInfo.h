#ifndef MUSICINFO_H_H_HEAD__FILE__
#define MUSICINFO_H_H_HEAD__FILE__
#include <QUrl>

#include <base/baseObject/baseObject.h>

class QMediaPlayer;
class MusicInfo : public BaseObject {
	Q_OBJECT;
protected:
	/// @brief 媒体
	QMediaPlayer *mediaPlayer;
	/// @brief 是否已经读取完毕
	bool isReadMusicFileOver = false;
	/// @brief 调用
	std::function< void( MusicInfo * ) > loadOverCallFunction;
	/// @brief 音乐文件路径
	QUrl musicUrl;
	/// @brief 音乐名称
	QString musicName;
	/// @brief 歌手
	QString singer;
	/// @brief 时长（毫秒）
	qint64 duration_ms;
public:
	~MusicInfo( ) override;
	MusicInfo( );
	virtual bool isOpenOver( ) const { return isReadMusicFileOver; }
	virtual bool open( const QString &file_path, const std::function< void( MusicInfo * ) > &load_over_call_function );
	virtual const QUrl & getMusicUrl( ) const { return musicUrl; }
	virtual const QString & getMusicName( ) const { return musicName; }
	virtual const QString & getSinger( ) const { return singer; }
	virtual qint64 getDurationMs( ) const { return duration_ms; }
};

#endif // MUSICINFO_H_H_HEAD__FILE__
