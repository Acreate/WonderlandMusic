#ifndef MUSICITEM_H_H_HEAD__FILE__
#define MUSICITEM_H_H_HEAD__FILE__
#include <QObject>
#include <QString>

#include <interface/iAppJsonData.h>

class MusicWindow;
class MusicListWidget;
class QMediaPlayer;

class MusicItem : public QObject, public IAppJsonData {
	Q_OBJECT;
	friend class MusicWindow;
	friend class MusicListWidget;

private:
	quint64 idCode;
	QString name;
	QString singer;
	QString filePath;
	qint64 elapsedTime;
	QMediaPlayer *mediaPlayer;
	bool loadedOver;
	QImage *rendBuff = nullptr;
	MusicWindow *musicWindow;

protected:
	MusicItem( );
	MusicItem( MusicWindow *music_window );

public:
	~MusicItem( ) override;
	MusicItem( MusicWindow *music_window, const QString &file_path );
	virtual bool isLoadedOver( );
	virtual bool getIdCode( quint64 &result_id_code ) const;
	virtual bool getName( QString &result_name ) const;
	virtual bool getSinger( QString &result_singer ) const;
	virtual bool getFilePath( QString &result_file_path ) const;
	virtual bool getElapsedTime( qint64 &result_elapsed_time ) const;
	virtual QImage * getRendBuff( ) const;
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
};

#endif // MUSICITEM_H_H_HEAD__FILE__
