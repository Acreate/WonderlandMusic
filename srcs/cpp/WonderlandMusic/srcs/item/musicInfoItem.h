#ifndef MUSICINFOITEM_H_H_HEAD__FILE__
#define MUSICINFOITEM_H_H_HEAD__FILE__

#include <qtypes.h>

#include "../component/musicWindow/interface/item/iMusicItem.h"

class MusicItemWidget;
class QMediaPlayer;

class MusicInfoItem : public QObject, public IMusicItem {
	Q_OBJECT;
	friend class AppMusicManage;

protected:
	UserMutex *userMutex;
	size_t idCode;
	QString name;
	QString singer;
	QString filePath;
	QString absoluteFilePath;
	QString elapsedTimeString;
	qint64 elapsedTime;
	bool loadedOver;
	QMediaPlayer *mediaPlayer = nullptr;
	AppMusicManage *appMusicManage;
	MusicCentreWidget *musicCentreWidget = nullptr;
	MusicItemWidget* musicItemWidget = nullptr;
protected:
	bool setMusicCentreWidget( MusicCentreWidget *music_centre_widget ) override;

public:
	explicit MusicInfoItem( AppMusicManage *app_music_manage );
	explicit MusicInfoItem( AppMusicManage *app_music_manage, const QString &disk_file_path );
	bool getElapsedTimeString( QString &result_elapsed_time_string ) const override;
	~MusicInfoItem( ) override;
	bool isLoadedOver( ) override;
	bool getIdCode( size_t &result_id_code ) const override;
	bool getName( QString &result_name ) const override;
	bool getSinger( QString &result_singer ) const override;
	bool getFilePath( QString &result_file_path ) const override;
	bool getElapsedTime( size_t &result_elapsed_time ) const override;
	virtual void setIdCode( const size_t id_code );
	virtual void setName( const QString &name );
	virtual void setSinger( const QString &singer );
	virtual void setAbsoluteFilePath( const QString &absolute_file_path );
	virtual void setElapsedTime( const qint64 elapsed_time );
	virtual void setLoadedOver( const bool loaded_over );
	MusicCentreWidget * getMusicCentreWidget( ) const override;
	IMusicItemWidget * getMusicItemWidget( ) const override;
};

#endif // MUSICINFOITEM_H_H_HEAD__FILE__
