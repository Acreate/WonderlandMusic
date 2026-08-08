#ifndef MUSICLOADTOOLS_H_H_HEAD__FILE__
#define MUSICLOADTOOLS_H_H_HEAD__FILE__

#include <interface/iAppCore.h>

class FavoriteItem;
class MusicCentreWidget;
class MusicFavoriteWidget;
class UserMutex;
class MusicItem;
class MusicListWidget;
class QString;

class MusicLoad : public IAppCore {
	friend class MusicLoadTools;

protected:
	std::vector< MusicItem * > loadMusicItemsHistory;
	MusicCentreWidget *musicCentreWidget;
	UserMutex *userMutex = nullptr;
	MusicLoad( MusicCentreWidget *music_centre_widget );
	~MusicLoad( ) override;

protected:
	bool deleteResource( ) override;
	virtual void unsafeDeleteMusicItemsHistory( );
	virtual bool unsafeHasMusicLoadMusicFileHistory( const QString &music_file ) const;
	virtual bool unsafeRemoveMusicItemsHistory( const MusicItem *music_item );

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
	virtual bool loadMusicFile( const QString &music_file_path );
	virtual bool loadMusicDir( const QString &music_dir_path );
	virtual bool removeMusicItemsHistory( const MusicItem *music_item );
	virtual bool hasMusicLoadMusicFileHistory( const QString &music_file );
	virtual FavoriteItem * getCurrentFavoriteItem( ) const;
};

class MusicLoadTools {
	friend class MusicLoad;
	friend class MusicFavoriteWidget;
	static bool createMusicLoad( MusicLoad **music_load, MusicCentreWidget *music_centre_widget );
	static bool releaseMusicLoad( MusicLoad **music_load );
	static bool setMusicListWidget( MusicLoad *music_load, MusicCentreWidget *music_centre_widget );
};
#endif // MUSICLOADTOOLS_H_H_HEAD__FILE__
