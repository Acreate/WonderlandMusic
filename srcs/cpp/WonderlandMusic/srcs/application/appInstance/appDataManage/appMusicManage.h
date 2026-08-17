#ifndef APPMUSICMANAGE_H_H_HEAD__FILE__
#define APPMUSICMANAGE_H_H_HEAD__FILE__

#include <interface/iAppCore.h>
#include <interface/iAppJsonData.h>
class IMusicFavoriteItem;
class IMusicItemWidthInfo;
class IItemWidthInfo;
class IMusicItem;
class QPainter;
class UserMutex;
class AppMusicDecoder;

class AppMusicManage : public QObject, public IAppCore, public IAppJsonData {
	Q_OBJECT;

protected:
	UserMutex *userMutex = nullptr;
	AppMusicDecoder *appMusicDecoder = nullptr;
	IMusicItemWidthInfo *musicItemWidthInfo = nullptr;
	std::vector< IMusicItem * > musicItemVector;
	std::vector< IMusicFavoriteItem * > musicFavoriteItemVector;

protected:
	bool deleteResource( ) override;
	virtual bool unsafeClearMusicItemVector( );
	virtual bool unsafeClearMusicFavoriteItem( );

	virtual bool renderImage( QPainter &painter, int intervalWidth, size_t index, IMusicItem *music_item, int calculate_min_width, int calculate_height, const QFont &font, const QColor &fill_separator_color ) const;
	virtual bool renderImage( size_t index, IMusicItem *music_item ) const;

public:
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;

	bool init( ) override;
	bool initBefore( ) override;
	bool initAfter( ) override;

	virtual AppMusicDecoder * getAppMusicDecoder( ) const;

public:
	virtual size_t loadMusicFile( const std::vector< QString > &music_file_path_vector );
	virtual size_t loadMusicFile( const std::list< QString > &music_file_path_list );
	virtual size_t loadMusicFile( const QStringList &music_file_path_list );
	virtual size_t loadMusicFile( const QString &music_file_path );
	virtual bool loadMusicDir( const QString &music_dir_path );
	virtual bool unsafeClear( );

public:
	virtual bool getMusicWindowInfoJsonData( QJsonObject &result_json_object );
	virtual bool setMusicWindowInfoJsonData( const QJsonObject &result_json_object );
	virtual bool hasMusicFile( const QString &file_path ) const;
	virtual bool updateMusicItem( IMusicItem *music_item );
	virtual bool removeMusicItem( IMusicItem *music_item );
	virtual bool hasMusicItem( size_t &result_index, const IMusicItem *music_item ) const;
	virtual bool clear( );
	virtual const IMusicItemWidthInfo & getMusicItemWidthInfo( ) const;
	virtual bool setMusicItemWidthInfo( const IMusicItemWidthInfo &music_item_width_info );
};
#endif // APPMUSICMANAGE_H_H_HEAD__FILE__
