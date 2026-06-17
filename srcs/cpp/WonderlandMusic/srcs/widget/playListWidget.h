#ifndef PLAYLISTWIDGET_H_H_HEAD__FILE__
#define PLAYLISTWIDGET_H_H_HEAD__FILE__

#include <QWidget>
class QMutex;
class MusicInfoItemWidget;
class QMediaMetaData;

class PlayListWidget : public QWidget {
	Q_OBJECT;
protected:
	QMutex *loadMusicFileMutex;
	QStringList loadMusicFileHistory;
	QVector< MusicInfoItemWidget * > musicInfoVector;
public:
	void clearMusicInfoVector( );
	~PlayListWidget( ) override;
	PlayListWidget( QWidget *parent );
	virtual bool loadJsonPathInfo( );
	virtual bool writeJsonPathInfo( );
	virtual bool appendItem( const QString &music_file_path, const QString &music_name, const QString &music_singer, const qint64 &duration );
	virtual bool fromFileLoadItemInfo( const QString &music_file_path );
	virtual QVector< MusicInfoItemWidget * > getMusicInfoVector( ) const;
	virtual QVector< QString > getListMusicFile( ) const;
};

#endif // PLAYLISTWIDGET_H_H_HEAD__FILE__
