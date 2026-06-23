#ifndef MUSICPLAYER_H_H_HEAD__FILE__
#define MUSICPLAYER_H_H_HEAD__FILE__
#include <QObject>

class MusicDecode;
class QAudioOutput;
class QMediaPlayer;
class QAudioFormat;
class QAudioDecoder;
class QAudioSink;

class MusicPlayer : public QObject {
	Q_OBJECT;

protected:
	QAudioOutput *audioOutput;
	QAudioSink *audioSink = nullptr;
	MusicDecode *musicDecode = nullptr;
	QIODevice *ioAudioSinkDevice;
	QString musicFilePath;

protected:
	virtual void deleteResource( );

public:
	MusicPlayer( QObject *parent = nullptr );

	virtual bool init( );

	virtual bool playerMusic( const QString &music_file );
};

#endif // MUSICPLAYER_H_H_HEAD__FILE__
