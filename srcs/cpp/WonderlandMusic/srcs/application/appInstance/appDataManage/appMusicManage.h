#ifndef APPMUSICMANAGE_H_H_HEAD__FILE__
#define APPMUSICMANAGE_H_H_HEAD__FILE__

#include <interface/iAppCore.h>
#include <interface/iAppJsonData.h>
class FavoriteItem;
class QPainter;
class ItemWidthInfo;
class MusicLoad;
class MusicItem;
class UserMutex;
class AppMusicDecoder;

class AppMusicManage : public QObject, public IAppCore, public IAppJsonData {
	Q_OBJECT;

protected:
	UserMutex *userMutex = nullptr;
	AppMusicDecoder *appMusicDecoder = nullptr;

	std::vector< MusicItem * > musicItemVector;
	MusicLoad *musicLoad = nullptr;

protected:
	bool deleteResource( ) override;

	virtual bool renderImage( QPainter &painter, int intervalWidth, size_t index, MusicItem *music_item, int calculate_min_width, int calculate_height, const QFont &font, const QColor &fill_separator_color ) const;
	virtual bool renderImage( size_t index, MusicItem *music_item ) const;

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
	virtual bool removeMusicLoad( MusicLoad *music_load );
	virtual bool hasMusicFile( const QString &file_path ) const;
	virtual bool updateMusicItem( MusicItem *music_item );
	virtual bool removeMusicItem( MusicItem *music_item );
	virtual bool hasMusicItem( size_t &result_index, const MusicItem *music_item ) const;
	virtual bool addMusicItem( MusicItem *music_item );
	virtual bool clear( );
	virtual const ItemWidthInfo & getItemWidthInfo( ) const;
	virtual void setItemWidthInfo( const ItemWidthInfo &item_width_info );
};
#endif // APPMUSICMANAGE_H_H_HEAD__FILE__
