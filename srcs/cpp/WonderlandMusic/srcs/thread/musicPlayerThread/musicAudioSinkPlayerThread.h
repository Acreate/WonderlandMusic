#ifndef MUSICAUDIOSINKPLAYERTHREAD_H_H_HEAD__FILE__
#define MUSICAUDIOSINKPLAYERTHREAD_H_H_HEAD__FILE__

#include "../musicPlayerThread.h"

class QAudioDecoder;
class QAudioOutput;
class QBuffer;
class QAudioDevice;
class QAudioSink;
class QAudioBuffer;
class QAudioFormat;

class MusicAudioSinkPlayerThread : public MusicPlayerThread {
	Q_OBJECT;

protected:
	std::vector< QAudioBuffer > audioBufferVector;
	QAudioSink *audioSink = nullptr;
	QIODevice *ioAudioSinkDevice;
	QAudioOutput *audioOutput;
	QAudioDecoder *audioDecoder = nullptr;

	bool startPlayerTread( ) override;

public:
	MusicAudioSinkPlayerThread( const QString &load_music_file );

	~MusicAudioSinkPlayerThread( ) override;

	bool setPlayerMusicPosition( qint64 position ) override;

	bool setPlayerMusicDuration( qint64 duration ) override;

protected:
	bool playerThread( MusicPlayerThread *music_player_thread ) override;

public:
Q_SIGNALS :
	/// @brief 播放帧
	/// @param music_player_thread 线程对象
	/// @param audioSink 音频播放对象
	/// @param ioAudioSinkDevice 音频输出 io
	/// @param audio_buffer 帧数据

	void playerMusicFrame( MusicAudioSinkPlayerThread *music_player_thread, QAudioSink *audioSink, QIODevice *ioAudioSinkDevice, const QAudioBuffer &audio_buffer );

	/// @brief 音频播放完毕
	/// @param music_player_thread 线程对象
	void overPlayerMusic( MusicAudioSinkPlayerThread *music_player_thread );
};

#endif // MUSICAUDIOSINKPLAYERTHREAD_H_H_HEAD__FILE__
