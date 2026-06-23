#ifndef MUSICPLAYER_H_H_HEAD__FILE__
#define MUSICPLAYER_H_H_HEAD__FILE__
#include <QObject>

class QAudioDevice;
class QAudioBuffer;
class MusicPlayerThread;
class MusicDecode;
class QAudioOutput;
class QMediaPlayer;
class QAudioFormat;
class QAudioDecoder;
class QAudioSink;

class MusicPlayer : public QObject {
	Q_OBJECT;

protected:
	MusicDecode *musicDecode = nullptr;
	QString musicFilePath;
	bool isPlayerMisucFile;
	bool isStop;

protected:
	virtual void deleteResource( );

	/// @brief 播放帧
	/// @param music_player_thread 线程对象
	/// @param audioSink 音频播放对象
	/// @param ioAudioSinkDevice 音频输出 io
	/// @param audio_buffer 帧数据
	void playerMusicFrame( MusicPlayerThread *music_player_thread, QAudioSink *audioSink, QIODevice *ioAudioSinkDevice, const QAudioBuffer &audio_buffer );

	/// @brief 音频播放完毕
	/// @param music_player_thread 线程对象
	void overPlayerMusic( MusicPlayerThread *music_player_thread );

public:
	MusicPlayer( QObject *parent = nullptr );

	~MusicPlayer( ) override;

	virtual bool init( );

	virtual bool playerMusic( const QString &music_file );
};

#endif // MUSICPLAYER_H_H_HEAD__FILE__
