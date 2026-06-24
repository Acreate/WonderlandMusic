#ifndef MUSICPLAYER_H_H_HEAD__FILE__
#define MUSICPLAYER_H_H_HEAD__FILE__
#include <QObject>

class QAudioDevice;
class QAudioBuffer;
class MusicPlayerThread;
class MusicDecode;
class QAudioOutput;
class QMediaPlayer;
class QAudioFormat;
class QAudioDecoder;
class QAudioSink;

class MusicPlayer : public QObject {
	Q_OBJECT;

protected:
	MusicDecode *musicDecode = nullptr;
	QString musicFilePath;
	bool isPlayerMisucFile;
	bool isStop;

protected:
	virtual void deleteResource( );

public:
	MusicPlayer( QObject *parent = nullptr );

	~MusicPlayer( ) override;

	virtual bool init( );

	virtual bool playerMusic( const QString &music_file );
};

#endif // MUSICPLAYER_H_H_HEAD__FILE__
