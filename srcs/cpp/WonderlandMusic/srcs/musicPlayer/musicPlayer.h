#ifndef MUSICPLAYER_H_H_HEAD__FILE__
#define MUSICPLAYER_H_H_HEAD__FILE__
#include <QObject>

#include "../application/appCore.h"

class QAudioDevice;
class QAudioBuffer;
class MusicPlayerThread;
class MusicDecode;
class QAudioOutput;
class QMediaPlayer;
class QAudioFormat;
class QAudioDecoder;
class QAudioSink;

class MusicPlayer : public QObject, public AppCore {
	Q_OBJECT;

protected:
	QString musicFilePath;
	MusicPlayerThread *musicPlayerThread = nullptr;

protected:
	bool deleteResource( ) override;

public:
	MusicPlayer( QObject *parent = nullptr );

	~MusicPlayer( ) override;

	bool init( ) override;

	virtual bool playerMusic( const QString &music_file );

	virtual const QString & getMusicFilePath( ) const;

	virtual bool getIsStop( ) const;

	virtual bool playerStop( );

	virtual qint64 getDuratction( ) const;

Q_SIGNALS:
	void playerOver( );

	void playerStart( );

	void playerDuration( );
};

#endif // MUSICPLAYER_H_H_HEAD__FILE__
