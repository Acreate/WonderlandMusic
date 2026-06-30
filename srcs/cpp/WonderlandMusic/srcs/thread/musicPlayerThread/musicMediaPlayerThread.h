#ifndef MUSICMEDIAPLAYERTHREAD_H_H_HEAD__FILE__
#define MUSICMEDIAPLAYERTHREAD_H_H_HEAD__FILE__

#include "../musicPlayerThread.h"

class QAudioOutput;
class QMediaPlayer;

class MusicMediaPlayerThread : public MusicPlayerThread {
	Q_OBJECT;

protected:
	QMediaPlayer *mediaPlayer = nullptr;
	QAudioOutput *audioOutput = nullptr;

	bool startPlayerTread( ) override;

public:
	bool stopPlayerMusic( ) override;

	MusicMediaPlayerThread( const QString &load_file_path );

	~MusicMediaPlayerThread( ) override;

	qint64 getDuratction( ) const override;

protected:
	bool playerThread( MusicPlayerThread *music_player_thread ) override;
};

#endif // MUSICMEDIAPLAYERTHREAD_H_H_HEAD__FILE__
