#ifndef MUSICINFOITEMWIDGET_H_H_HEAD__FILE__
#define MUSICINFOITEMWIDGET_H_H_HEAD__FILE__
#include <QWidget>

#include "../application/appJsonData.h"
#include "../application/appRenderBuff.h"

class QMediaMetaData;

class MusicInfoItemWidget : public QWidget, public AppJsonData, public AppRenderBuff {
	Q_OBJECT;
	friend class PlayerWindow;
	friend class PlayerListWidget;

protected:
	bool equFilePath;
	QString absFilePath;
	QString musicFilePath;
	QString musicName;
	QString musicSinger;
	qint64 duration;
	QString formatStringDuration;
	size_t index;
	QString formatStringIndex;

	int widgetBeforeWidth;
	int widgetAfterWidth;
	int splitWidth;
	int indexWidth;
	int musicNameWidth;
	int musicSingerWidth;
	int musicDurationWidth;

public:
	MusicInfoItemWidget( );

	MusicInfoItemWidget( QWidget *parent );

	bool renderToBuff( ) override;

	bool getJsonData( QJsonObject &get_json_object ) const override;

	bool setJsonData( const QJsonObject &set_json_object ) override;

	virtual bool init( const QString &music_file_path, const QString &music_name, const QString &music_singer, qint64 duration_ms );

	virtual bool init( const QString &file_path, const QMediaMetaData &mediaMetaData );

	virtual bool isFile( const QString &comp_file ) const;

	virtual const QString & getMusicFilePath( ) const;

	virtual const QString & getMusicName( ) const;

	virtual const QString & getMusicSinger( ) const;

	virtual qint64 getDuration( ) const;

	virtual const QString & getFormatStringDuration( ) const;

	static bool toJsonObect( QJsonObject &result_json_object, const MusicInfoItemWidget &music_info );

	static bool forJsonObject( MusicInfoItemWidget &result_music_info, const QJsonObject &for_json_object );

	virtual size_t getIndex( ) const;

	virtual void setIndex( const size_t index );

	virtual const QString & getFormatStringIndex( ) const;

protected:
	void paintEvent( QPaintEvent *event ) override;
};

#endif // MUSICINFOITEMWIDGET_H_H_HEAD__FILE__
