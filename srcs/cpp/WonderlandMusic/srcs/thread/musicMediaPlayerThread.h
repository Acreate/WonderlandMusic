#ifndef MUSICMEDIAPLAYERTHREAD_H_H_HEAD__FILE__
#define MUSICMEDIAPLAYERTHREAD_H_H_HEAD__FILE__
#include <QThread>

class QAudioOutput;
class QMediaPlayer;

class MusicMediaPlayerThread : public QThread {
	Q_OBJECT;

protected:
	QString load_file_path;
	bool isJump;
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

	virtual void stop( );

protected:
	void run( ) override;

Q_SIGNALS:
	void positionChanged( qint64 position );

	void durationChanged( qint64 duration );
};

#endif // MUSICMEDIAPLAYERTHREAD_H_H_HEAD__FILE__
