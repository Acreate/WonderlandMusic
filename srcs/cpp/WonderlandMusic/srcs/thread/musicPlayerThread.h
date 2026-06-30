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

protected:
	virtual bool startPlayerTread( );

	virtual bool playerThread( MusicPlayerThread *music_player_thread ) = 0;

public:
	MusicPlayerThread( const QString &music_file_path );

	~MusicPlayerThread( ) override;

	virtual bool isIsRunOver( ) const;

	virtual unsigned long getControlGepTime( ) const;

	virtual bool stopPlayerMusic( );

	virtual bool startPlayerMusic( );

	virtual void setPlayerMusicPosition( qint64 position );

	virtual void setPlayerMusicDuration( qint64 duration );

	virtual void setControlGepTime( const unsigned long control_gep_time );

	virtual qint64 getDuratction( ) const = 0;

Q_SIGNALS:
	void positionChange( qint64 position );

	void durationChange( qint64 use_duration );

	void threadOver( );

	void threadStart( );
};

#endif // MUSICPLAYERTHREAD_H_H_HEAD__FILE__
