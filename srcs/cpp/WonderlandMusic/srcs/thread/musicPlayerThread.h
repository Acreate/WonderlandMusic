#ifndef MUSICPLAYERTHREAD_H_H_HEAD__FILE__
#define MUSICPLAYERTHREAD_H_H_HEAD__FILE__
#include <QThread>

class QAudioBuffer;
class QAudioFormat;

class MusicPlayerThread : public QThread {
	Q_OBJECT;

protected:
	std::vector< QAudioBuffer > audioBufferVector;
	bool isJuimp;

public:
	MusicPlayerThread( const std::vector< QAudioBuffer > &audio_buffer_vector );

	~MusicPlayerThread( ) override;

	virtual void stop( );

protected:
	void run( ) override;

Q_SIGNALS:
	/// @brief 播放帧
	/// @param music_player_thread 线程对象
	/// @param audio_buffer 帧数据
	void playerMusicFrame( MusicPlayerThread *music_player_thread, const QAudioBuffer &audio_buffer );

	/// @brief 音频播放完毕
	/// @param music_player_thread 线程对象
	void overPlayerMusic( MusicPlayerThread *music_player_thread );
};

#endif // MUSICPLAYERTHREAD_H_H_HEAD__FILE__
