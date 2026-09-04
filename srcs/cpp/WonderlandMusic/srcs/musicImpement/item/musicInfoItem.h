#ifndef MUSICINFOITEM_H_H_HEAD__FILE__
#define MUSICINFOITEM_H_H_HEAD__FILE__

#include <component/musicWindow/interface/item/iMusicItem.h>

class MusicInfo;
class MusicItemWidget;
class QMediaPlayer;

class MusicInfoItem : public QObject, public IMusicItem {
	Q_OBJECT;
	friend class AppMusicManage;
	friend class MusicFavoriteItem;

protected:
	size_t idCode;
	QString fileBaseName;
	QString name;
	QString singer;
	QString filePath;
	QString absoluteFilePath;
	QString elapsedTimeString;
	qint64 elapsedTime;
	IMusicCentreWidget *musicCentreWidget = nullptr;
	MusicItemWidget *musicItemWidget = nullptr;
	IMusicFavoriteItem *musicFavoriteItem = nullptr;

protected:
	virtual bool initVar( const MusicInfo &music_info );
	~MusicInfoItem( ) override;

public:
	explicit MusicInfoItem( IMusicFavoriteItem *music_favorite_item, const MusicInfo &music_info );
	explicit MusicInfoItem( IMusicFavoriteItem *music_favorite_item );
	bool setMusicCentreWidget( IMusicCentreWidget *music_centre_widget ) override;
	bool setMusicFavoriteItem( IMusicFavoriteItem *music_favorite_item ) override;
	size_t getIdCode( ) const override;
	const QString & getName( ) const override;
	const QString & getSinger( ) const override;
	const QString & getFilePath( ) const override;
	const QString & getAbsoluteFilePath( ) const override;
	const QString & getElapsedTimeString( ) const override;
	const qint64 & getElapsedTime( ) const override;
	const QString & getFileBaseName( ) const override;
	void setIdCode( const size_t id_code ) override;
	void setName( const QString &name ) override;
	void setSinger( const QString &singer ) override;
	void setAbsoluteFilePath( const QString &absolute_file_path ) override;
	void setElapsedTime( const qint64 elapsed_time ) override;
	IMusicCentreWidget * getMusicCentreWidget( ) const override;
	IMusicItemWidget * getMusicItemWidget( ) const override;
	IMusicFavoriteItem * getMusicFavoriteItem( ) const override;
};

#endif // MUSICINFOITEM_H_H_HEAD__FILE__
