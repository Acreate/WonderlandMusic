#ifndef MUSICLOAD_H_H_HEAD__FILE__
#define MUSICLOAD_H_H_HEAD__FILE__

#include <interface/iAppCore.h>

class UserMutex;
class MusicItem;
class AppMusicManage;

class MusicLoad : public IAppCore {
protected:
	std::vector< MusicItem * > loadMusicItemsHistory;
	AppMusicManage *appMusicManage;
	UserMutex *userMutex = nullptr;

public:
	MusicLoad( AppMusicManage *app_music_manage );
	~MusicLoad( ) override;

protected:
	bool deleteResource( ) override;
	virtual void unsafeDeleteMusicItemsHistory( );
	virtual bool unsafeHasMusicLoadMusicFileHistory( const QString &music_file ) const;
	virtual bool unsafeRemoveMusicItemsHistory( const MusicItem *music_item );

	virtual bool removeMusicItemsHistory( const MusicItem *music_item );
	virtual bool hasMusicLoadMusicFileHistory( const QString &music_file );

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
	virtual size_t loadMusicFile( const std::vector< QString > &music_file_path_vector );
	virtual size_t loadMusicFile( const std::list< QString > &music_file_path_list );
	virtual size_t loadMusicFile( const QStringList &music_file_path_list );
	virtual size_t loadMusicFile( const QString &music_file_path );
	virtual bool loadMusicDir( const QString &music_dir_path );
	virtual FavoriteItem * getFavoriteItem( ) const;
	virtual bool update( );
};

#endif // MUSICLOAD_H_H_HEAD__FILE__
