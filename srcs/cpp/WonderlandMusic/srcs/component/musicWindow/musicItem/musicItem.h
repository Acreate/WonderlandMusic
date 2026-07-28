#ifndef MUSICITEM_H_H_HEAD__FILE__
#define MUSICITEM_H_H_HEAD__FILE__
#include <QObject>
#include <QString>

class MusicWindow;
class QMediaPlayer;

class MusicItem : public QObject {
	Q_OBJECT;
	friend class MusicWindow;

private:
	quint64 idCode;
	QString name;
	QString singer;
	QString filePath;
	qint64 elapsedTime;
	QMediaPlayer *mediaPlayer;
	bool loadedOver;
	MusicWindow *musicWindow;

public:
	~MusicItem( ) override;
	MusicItem( MusicWindow *music_window, const QString &file_path );
	virtual bool isLoadedOver( );
	virtual bool getIdCode( quint64 &result_id_code ) const;
	virtual bool getName( QString &result_name ) const;
	virtual bool getSinger( QString &result_singer ) const;
	virtual bool getFilePath( QString &result_file_path ) const;
	virtual bool getElapsedTime( qint64 &result_elapsed_time ) const;
};

#endif // MUSICITEM_H_H_HEAD__FILE__
