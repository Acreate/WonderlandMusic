#ifndef MUSICPLAYERTHREAD_H_H_HEAD__FILE__
#define MUSICPLAYERTHREAD_H_H_HEAD__FILE__
#include <QThread>

class QAudioOutput;
class QBuffer;
class QAudioDevice;
class QAudioSink;
class QAudioBuffer;
class QAudioFormat;

class MusicPlayerThread : public QThread {
	Q_OBJECT;

protected:
	MusicPlayerThread * currentThisPtr;
	std::vector< QAudioBuffer > audioBufferVector;
	bool isJuimp;
	QAudioSink *audioSink = nullptr;
	QIODevice *ioAudioSinkDevice;
	QAudioOutput* audioOutput;

public:
	MusicPlayerThread( const std::vector< QAudioBuffer > &audio_buffer_vector );

	~MusicPlayerThread( ) override;

	virtual void stop( );

protected:
	void run( ) override;

Q_SIGNALS:
	/// @brief 播放帧
	/// @param music_player_thread 线程对象
	/// @param audioSink 音频播放对象
	/// @param ioAudioSinkDevice 音频输出 io
	/// @param audio_buffer 帧数据
	void playerMusicFrame( MusicPlayerThread *music_player_thread, QAudioSink *audioSink, QIODevice *ioAudioSinkDevice, const QAudioBuffer &audio_buffer );

	/// @brief 音频播放完毕
	/// @param music_player_thread 线程对象
	void overPlayerMusic( MusicPlayerThread *music_player_thread );
};

#endif // MUSICPLAYERTHREAD_H_H_HEAD__FILE__
