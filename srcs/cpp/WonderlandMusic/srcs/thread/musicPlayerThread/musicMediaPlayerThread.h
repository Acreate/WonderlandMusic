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
protected:
	virtual bool initVar( );

	virtual bool initSource( );

	virtual bool initConnectSignals( );

	virtual bool initStartStatus( );

public:
	MusicMediaPlayerThread( const QString &load_file_path );

	~MusicMediaPlayerThread( ) override;

	bool setPlayerMusicPosition( qint64 position ) override;

	bool setPlayerMusicDuration( qint64 duration ) override;

protected:
	bool playerThread( MusicPlayerThread *music_player_thread ) override;
};

#endif // MUSICMEDIAPLAYERTHREAD_H_H_HEAD__FILE__
