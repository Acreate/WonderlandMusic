#ifndef MUSICINFOITEMWIDGET_H_H_HEAD__FILE__
#define MUSICINFOITEMWIDGET_H_H_HEAD__FILE__
#include <QWidget>
class QMediaMetaData;
class MusicInfoItemWidget : public QWidget {
	Q_OBJECT;
protected:
	QString musicFilePath;
	QString musicName;
	QString musicSinger;
	qint64 duration;
	QString formatStringDuration;
public:
	MusicInfoItemWidget(  );
	MusicInfoItemWidget( QWidget *parent );
	virtual bool init( const QString &music_file_path, const QString &music_name, const QString &music_singer, qint64 duration_ms );
	virtual bool init( const QString &file_path, const QMediaMetaData &mediaMetaData );
	virtual const QString & getMusicFilePath( ) const { return musicFilePath; }
	virtual const QString & getMusicName( ) const { return musicName; }
	virtual const QString & getMusicSinger( ) const { return musicSinger; }
	virtual qint64 getDuration( ) const { return duration; }
	virtual const QString & getFormatStringDuration( ) const { return formatStringDuration; }
	static bool toJsonObect( QJsonObject &result_json_object, const MusicInfoItemWidget &music_info );
	static bool forJsonObject( MusicInfoItemWidget &result_music_info, const QJsonObject &for_json_object );
};

#endif // MUSICINFOITEMWIDGET_H_H_HEAD__FILE__
