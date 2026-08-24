#ifndef APPMUSICMANAGE_H_H_HEAD__FILE__
#define APPMUSICMANAGE_H_H_HEAD__FILE__

#include <interface/iAppCore.h>
#include <interface/iAppJsonData.h>

#include "../../../component/musicWindow/interface/info/iMusicDataManage.h"

#include "../../../interface/iAppResourceCore.h"
class IMusicFavoriteItem;
class IMusicItemWidthInfo;
class MusicFavoriteItem;
class MusicInfoItem;

class IMusicItem;
class QPainter;
class UserMutex;
class AppMusicDecoder;

class AppMusicManage : public QObject, public IMusicDataManage, public IAppJsonData, public IAppResourceCore {
	Q_OBJECT;

protected:
	UserMutex *userMutex = nullptr;
	AppMusicDecoder *appMusicDecoder = nullptr;
	IMusicItemWidthInfo *musicItemWidthInfo = nullptr;
	std::vector< MusicInfoItem * > musicItemVector;
	std::vector< MusicFavoriteItem * > musicFavoriteItemVector;
	MusicCentreWidget *musicCentreWidget = nullptr;

protected:
	bool deleteResource( ) override;
	virtual bool unsafeClearMusicItemVector( );
	virtual bool unsafeClearMusicFavoriteItem( );

public:
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;

	bool init( ) override;
	bool initBefore( ) override;
	bool initAfter( ) override;

	virtual AppMusicDecoder * getAppMusicDecoder( ) const;

public:
	virtual size_t loadMusicFile( IMusicFavoriteItem *music_favorite_item, const std::vector< QString > &music_file_path_vector );
	virtual size_t loadMusicFile( IMusicFavoriteItem *music_favorite_item, const std::list< QString > &music_file_path_list );
	virtual size_t loadMusicFile( IMusicFavoriteItem *music_favorite_item, const QStringList &music_file_path_list );
	virtual size_t loadMusicFile( IMusicFavoriteItem *music_favorite_item, const QString &music_file_path );
	virtual size_t loadMusicDir( IMusicFavoriteItem *music_favorite_item, const QString &music_dir_path );
	virtual bool unsafeClear( );

public:
	virtual bool getMusicWindowInfoJsonData( QJsonObject &result_json_object );
	virtual bool setMusicWindowInfoJsonData( const QJsonObject &result_json_object );
	virtual bool hasMusicFile( const QString &file_path ) const;
	virtual bool addMusicItem( IMusicItem *music_item );
	virtual bool updateMusicItem( IMusicItem *music_item );
	virtual bool removeMusicItem( IMusicItem *music_item );
	virtual bool hasMusicItem( size_t &result_index, const IMusicItem *music_item ) const;

	virtual const IMusicItemWidthInfo & getMusicItemWidthInfo( ) const;
	virtual bool setMusicItemWidthInfo( const IMusicItemWidthInfo &music_item_width_info );

protected:
	bool setMusicCentreWidget( MusicCentreWidget *music_centre_widget ) override;

public:
	MusicCentreWidget * getMusicCentreWidget( ) const override;
	bool getDefaultMusicFavoriteItem( IMusicFavoriteItem *&result_default_music_favorite_item ) const override;
	bool getIndexMusicFavoriteItem( IMusicFavoriteItem *&result_default_music_favorite_item, const size_t &index ) const override;
	bool getPosYMusicFavoriteItem( IMusicFavoriteItem *&result_default_music_favorite_item, const size_t &pos_x ) const override;
	bool getNameMusicFavoriteItem( IMusicFavoriteItem *&result_default_music_favorite_item, const QString &music_favorite_name ) const override;
	size_t getMusicNameVector( QString &result_default_music_favorite_name, std::vector< QString > &result_music_favorite_name_vector ) const override;
	size_t findMusicItemAtFavoriteItem( const IMusicItem *music_item, std::vector< IMusicFavoriteItem * > &result_find_favorite_vector ) const override;
	size_t findNameAtMusicItem( const QString &music_name, std::vector< IMusicItem * > &result_find_music_vector ) const override;
	size_t findSingerAtMusicItem( const QString &music_singer, std::vector< IMusicItem * > &result_find_music_vector ) const override;
	size_t findFileAtMusicItem( const QString &file_path, std::vector< IMusicItem * > &result_find_music_vector ) const override;
	bool initDefaultMusicFavoriteItem( ) override;
	bool clear( ) override;
};
#endif // APPMUSICMANAGE_H_H_HEAD__FILE__
