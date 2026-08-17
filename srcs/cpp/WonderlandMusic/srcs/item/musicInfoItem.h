#ifndef MUSICINFOITEM_H_H_HEAD__FILE__
#define MUSICINFOITEM_H_H_HEAD__FILE__
#include <QObject>
#include <QString>
#include <qtypes.h>

#include "../component/musicWindow/interface/item/iMusicItem.h"

class QMediaPlayer;

class MusicInfoItem : public QObject, public IMusicItem {
	Q_OBJECT;
	friend class AppMusicManage;

protected:
	size_t idCode;
	QString name;
	QString singer;
	QString filePath;
	QString absoluteFilePath;
	QString elapsedTimeString;
	qint64 elapsedTime;
	bool loadedOver;
	QMediaPlayer *mediaPlayer = nullptr;
	QImage *rendBuff = nullptr;
	AppMusicManage *appMusicManage;

protected:
	explicit MusicInfoItem( AppMusicManage *app_music_manage );
	explicit MusicInfoItem( AppMusicManage *app_music_manage, const QString &disk_file_path );

	bool setMusicCentreWidget( MusicCentreWidget *music_centre_widget ) override;

public:
	bool getElapsedTimeString( QString &result_elapsed_time_string ) const override;
	QImage * createResizeBuff( const int &width, const int &height ) override;
	~MusicInfoItem( ) override;
	bool isLoadedOver( ) override;
	bool getIdCode( size_t &result_id_code ) const override;
	bool getName( QString &result_name ) const override;
	bool getSinger( QString &result_singer ) const override;
	bool getFilePath( QString &result_file_path ) const override;
	bool getElapsedTime( size_t &result_elapsed_time ) const override;
	bool getRendBuff( QImage &result_buff ) const override;
};

#endif // MUSICINFOITEM_H_H_HEAD__FILE__
