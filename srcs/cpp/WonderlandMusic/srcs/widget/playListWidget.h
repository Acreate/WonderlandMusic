#ifndef PLAYLISTWIDGET_H_H_HEAD__FILE__
#define PLAYLISTWIDGET_H_H_HEAD__FILE__

#include <QWidget>
class MusicInfoItem;
class QMutex;
class MusicInfoItemWidget;
class QMediaMetaData;

class PlayListWidget : public QWidget {
	Q_OBJECT;
protected:
	QMutex *loadMusicFileMutex;
	QStringList loadMusicFileHistory;
	QVector< MusicInfoItem * > musicInfoVector;
	int splitWidth;
protected:
	virtual bool renderAtMusicInfoItem( QImage &result_render_image, MusicInfoItem *render_target, int font_ascent, int split_width, int name_item_width, int singer_item_width, int duration_item_width, const QFont *item_font ) const;
	virtual bool renderAtMusicInfoItem( QImage &result_render_image, MusicInfoItem *render_target ) const;
	virtual bool renderAtMusicInfoItem( QImage &result_render_image, MusicInfoItem *render_target, int split_width ) const;
public:
	void clearMusicInfoVector( );
	~PlayListWidget( ) override;
	PlayListWidget( QWidget *parent );
	virtual bool loadJsonPathInfo( );
	virtual bool writeJsonPathInfo( );
	virtual bool appendItem( const QString &music_file_path, const QString &music_name, const QString &music_singer, const qint64 &duration );
	virtual bool fromFileLoadItemInfo( const QString &music_file_path );
	virtual QVector< MusicInfoItem * > getMusicInfoVector( ) const;
	virtual QVector< QString > getListMusicFile( ) const;
	virtual bool renderMusicInfoItem( QImage &result_render_image, const MusicInfoItem *render_target ) const;
protected:
	void paintEvent( QPaintEvent *event ) override;
};

#endif // PLAYLISTWIDGET_H_H_HEAD__FILE__
