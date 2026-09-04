#ifndef MUSICFAVORITEITEM_H_H_HEAD__FILE__
#define MUSICFAVORITEITEM_H_H_HEAD__FILE__
#include <component/musicWindow/interface/item/iMusicFavoriteItem.h>

class MusicInfoItem;
class MusicFileInfo;
class MusicFavoriteItemWidget;

class MusicFavoriteItem : public QObject, public IMusicFavoriteItem {
	Q_OBJECT;

protected:
	UserMutex *musicFavoriteItemUserMutex;
	QString name;
	std::vector< MusicInfoItem * > musicItemVector;
	IMusicCentreWidget *musicCentreWidget = nullptr;
	MusicFavoriteItemWidget *musicFavoriteItemWidget = nullptr;

public:
	MusicFavoriteItem( );
	~MusicFavoriteItem( ) override;

public:
	bool setMusicCentreWidget( IMusicCentreWidget *music_centre_widget ) override;
	virtual MusicInfoItem * load( MusicFileInfo *music_info );
	virtual std::vector< MusicInfoItem * > load( const std::vector< MusicFileInfo * > &music_infos );
	bool getName( QString &result_name ) const override;
	bool removeMusicItem( IMusicItem *music_item ) override;
	bool clear( ) override;
	bool update( ) override;
	size_t getMusicVector( std::vector< IMusicItem * > &result_clone_vector ) const override;
	virtual void setName( const QString &name );
	IMusicCentreWidget * getMusicCentreWidget( ) const override;
	IMusicFavoriteItemWidget * getMusicFavoriteItemWidget( ) const override;
	bool loadMusicDirPath( const std::vector< QString > &music_file_path ) override;
	bool loadMusicFile( const std::vector< QString > &music_file_path ) override;
	bool loadMusicFile( const QString &music_file_path ) override;
};

#endif // MUSICFAVORITEITEM_H_H_HEAD__FILE__
