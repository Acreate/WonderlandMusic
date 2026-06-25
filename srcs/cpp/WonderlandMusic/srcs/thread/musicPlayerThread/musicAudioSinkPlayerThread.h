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

protected:
	bool playerThread( MusicPlayerThread *music_player_thread ) override;
};

#endif // MUSICAUDIOSINKPLAYERTHREAD_H_H_HEAD__FILE__
