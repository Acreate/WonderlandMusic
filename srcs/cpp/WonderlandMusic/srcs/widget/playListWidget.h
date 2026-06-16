#ifndef PLAYLISTWIDGET_H_H_HEAD__FILE__
#define PLAYLISTWIDGET_H_H_HEAD__FILE__

#include <QWidget>
#include <QMutex>
class QMediaMetaData;
class MusicInfo {
	QString musicFilePath;
	QString musicName;
	QString musicSinger;
	qint64 duration;
	QString formatStringDuration;
public:
	virtual ~MusicInfo( ) = default;
	MusicInfo( const QString &file_path, const QMediaMetaData &mediaMetaData );
	virtual const QString & getMusicFilePath( ) const { return musicFilePath; }
	virtual const QString & getMusicName( ) const { return musicName; }
	virtual const QString & getMusicSinger( ) const { return musicSinger; }
	virtual qint64 getDuration( ) const { return duration; }
	virtual const QString & getFormatStringDuration( ) const { return formatStringDuration; }
};
class PlayListWidget : public QWidget {
	Q_OBJECT;
protected:
	QMutex loadMusicFileMutex;
	QStringList loadMusicFileHistory;
	QVector< MusicInfo * > musicInfoVector;
public:
	void clearMusicInfoVector( );
	~PlayListWidget( ) override;
	PlayListWidget( QWidget *parent );
	virtual bool loadJsonPathInfo( );
	virtual bool writeJsonPathInfo( );
	virtual bool appendItem( const QString &music_file_path, const QString &music_name, const QString &music_singer, const qint64 &duration );
	virtual bool fromFileLoadItemInfo( const QString &music_file_path );
};

#endif // PLAYLISTWIDGET_H_H_HEAD__FILE__
