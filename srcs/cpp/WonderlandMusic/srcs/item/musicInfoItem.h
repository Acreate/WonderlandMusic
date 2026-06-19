#ifndef MUSICINFOITEM_H_H_HEAD__FILE__
#define MUSICINFOITEM_H_H_HEAD__FILE__
#include <QString>

class QImage;
class QJsonObject;
class PlayListWidget;
class QMediaMetaData;

class MusicInfoItem {
	friend class PlayListWidget;

protected:
	PlayListWidget *parentPlayListWidget;

	QString musicFilePath;
	QString musicName;
	QString musicSinger;
	qint64 duration;
	QString formatStringDuration;
	size_t index;
	QString formatStringIndex;
protected:
	MusicInfoItem( );

	MusicInfoItem( PlayListWidget *parent );

	virtual ~MusicInfoItem( ) = default;

public:
	virtual bool init( const QString &music_file_path, const QString &music_name, const QString &music_singer, qint64 duration_ms );

	virtual bool init( const QString &file_path, const QMediaMetaData &mediaMetaData );

	virtual const QString & getMusicFilePath( ) const;

	virtual const QString & getMusicName( ) const;

	virtual const QString & getMusicSinger( ) const;

	virtual qint64 getDuration( ) const;

	virtual const QString & getFormatStringDuration( ) const;

	static bool toJsonObect( QJsonObject &result_json_object, const MusicInfoItem &music_info );

	static bool forJsonObject( MusicInfoItem &result_music_info, const QJsonObject &for_json_object );

	virtual bool renderImage( QImage &result_render_image ) const;

	virtual size_t getIndex( ) const;

	virtual void setIndex( const size_t index );

	virtual const QString & getFormatStringIndex( ) const;
};

#endif // MUSICINFOITEM_H_H_HEAD__FILE__
