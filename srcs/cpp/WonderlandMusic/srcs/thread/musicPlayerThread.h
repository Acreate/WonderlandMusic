#ifndef MUSICPLAYERTHREAD_H_H_HEAD__FILE__
#define MUSICPLAYERTHREAD_H_H_HEAD__FILE__

#include <QThread>

class MusicPlayerThread : public QObject {
	Q_OBJECT;

protected:
	QString musicFilePath;
	bool isJump;
	unsigned long controlGepTime;

public:
	MusicPlayerThread( const QString &music_file_path );

	~MusicPlayerThread( ) override;

public:
	virtual bool startPlayerMusic( );

	virtual bool stopPlayerMusic( ) = 0;

	virtual bool setPlayerMusicPosition( qint64 position ) = 0;

	virtual bool setPlayerMusicDuration( qint64 duration ) = 0;

public:
	virtual unsigned long getControlGepTime( ) const;

	virtual void setControlGepTime( const unsigned long control_gep_time );

protected:
	virtual bool playerThread( MusicPlayerThread *music_player_thread ) = 0;

Q_SIGNALS:
	void positionChanged( qint64 position );

	void durationChanged( qint64 duration );

	void threadOver( );
};

#endif // MUSICPLAYERTHREAD_H_H_HEAD__FILE__
