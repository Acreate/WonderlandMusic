#ifndef MUSICPLAYER_H_H_HEAD__FILE__
#define MUSICPLAYER_H_H_HEAD__FILE__
#include <QObject>

class QAudioOutput;
class QMediaPlayer;
class QAudioFormat;
class QAudioDecoder;
class QAudioSink;

class MusicPlayer : public QObject {
	Q_OBJECT;

protected:
	QAudioOutput *audioOutput;
	QMediaPlayer *mediaPlayer = nullptr;
	QAudioSink *audioSink = nullptr;
	QAudioDecoder *audioDecoder = nullptr;
	QIODevice *ioDevice;
	QString musicFilePath;

protected:
	virtual void deleteResource( );

	// 信号
protected:
	virtual void bufferReady( );

	virtual void finished( );

	virtual void formatChanged( const QAudioFormat &fmt );

public:
	MusicPlayer( QObject *parent = nullptr );

	virtual bool init( );

	virtual bool playerMusic( const QString &music_file );
};

#endif // MUSICPLAYER_H_H_HEAD__FILE__
