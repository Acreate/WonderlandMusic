#ifndef MUSICLOAD_H_H_HEAD__FILE__
#define MUSICLOAD_H_H_HEAD__FILE__

#include <interface/iAppCore.h>

class FavoriteItem;
class MusicCentreWidget;
class MusicFavoriteWidget;
class UserMutex;
class MusicItem;
class MusicListWidget;
class QString;
class MusicLoadTools;

class MusicLoad : public IAppCore {
	friend class MusicLoadTools;

protected:
	std::vector< MusicItem * > loadMusicItemsHistory;
	FavoriteItem *favoriteItem;
	UserMutex *userMutex = nullptr;
	MusicLoad( FavoriteItem *favorite_item );
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
	virtual size_t loadMusicFile( const std::vector< QString > &music_file_path_vector );
	virtual size_t loadMusicFile( const std::list< QString > &music_file_path_list );
	virtual size_t loadMusicFile( const QStringList &music_file_path_list );
	virtual size_t loadMusicFile( const QString &music_file_path );
	virtual bool loadMusicDir( const QString &music_dir_path );
	virtual bool removeMusicItemsHistory( const MusicItem *music_item );
	virtual bool hasMusicLoadMusicFileHistory( const QString &music_file );
	virtual FavoriteItem * getFavoriteItem( ) const;
};

#endif // MUSICLOAD_H_H_HEAD__FILE__
