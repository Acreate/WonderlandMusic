#ifndef MUSIC_H_H_HEAD__FILE__
#define MUSIC_H_H_HEAD__FILE__
#include <QString>

class QUrl;
class QAudioDecoder;
class QMediaPlayer;
class QFileInfo;
class QImage;
class QDateTime;
/// @brief 音乐类
class Music {
private:
	/// @brief 音频解码器
	QAudioDecoder *audioDecoder;
	/// @brief 音频播放组件
	QMediaPlayer *mediaPlayer;
	/// @brief 路径检测对象
	QFileInfo *info;
private:
	/// @brief 音乐文件路径
	QUrl *musicUrl;
	/// @brief 音乐名称
	QString musicName;
	/// @brief 歌手
	QString singer;
	/// @brief 时长（毫秒）
	qint64 duration_ms;
public:
	virtual ~Music( );
	Music( );
	bool loadFile( const QString &music_path );
	virtual const QUrl * getMusicUrl( ) const { return musicUrl; }
	virtual const QAudioDecoder * getAudioDecoder( ) const { return audioDecoder; }
	virtual const QMediaPlayer * getMediaPlayer( ) const { return mediaPlayer; }
	virtual const QString & getMusicName( ) const { return musicName; }
	virtual const QString & getSinger( ) const { return singer; }
	virtual qint64 getDurationMs( ) const { return duration_ms; }
};

#endif // MUSIC_H_H_HEAD__FILE__
