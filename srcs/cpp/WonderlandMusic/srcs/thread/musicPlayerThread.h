#ifndef MUSICPLAYERTHREAD_H_H_HEAD__FILE__
#define MUSICPLAYERTHREAD_H_H_HEAD__FILE__

#include <QThread>

class QMutex;

class MusicPlayerThread : public QObject {
	Q_OBJECT;

protected:
	QString musicFilePath;
	bool isJump;
	unsigned long controlGepTime;
	bool isSetPos = false;
	quint64 pos = 0;
	qint64 duration;
	bool isRunOver = true;
	QMutex* sleepMutex = nullptr;

protected:
	virtual bool startPlayerTread( );

	virtual bool playerThread( MusicPlayerThread *music_player_thread ) = 0;

public:
	MusicPlayerThread( const QString &music_file_path );

	~MusicPlayerThread( ) override;

	virtual unsigned long getControlGepTime( ) const;

	virtual bool stopPlayerMusic( );

	virtual bool startPlayerMusic( );

	virtual void setPlayerMusicPosition( qint64 position );

	virtual void setPlayerMusicDuration( qint64 duration );

	virtual void setControlGepTime( const unsigned long control_gep_time );

Q_SIGNALS:
	void positionChanged( qint64 position );

	void durationChanged( qint64 duration );

	void threadOver( );

	void threadStart( );
};

#endif // MUSICPLAYERTHREAD_H_H_HEAD__FILE__
