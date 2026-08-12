#ifndef FAVORITEITEM_H_H_HEAD__FILE__
#define FAVORITEITEM_H_H_HEAD__FILE__
#include <interface/iAppJsonData.h>

#include "../../itemWidthInfo/itemWidthInfo.h"

class MusicLoad;
class MusicCentreWidget;
class QPainter;
class MusicTitleWidget;
class UserMutex;
class MusicItem;

class FavoriteItem : public QObject, public ItemWidthInfo {
	Q_OBJECT;
	friend class MusicFavoriteWidget;

protected:
	MusicCentreWidget *musicCentreWidget;
	QString favoriteItemName;
	std::vector< MusicItem * > musicItemVector;
	UserMutex *userMutex;

	QImage *drawBuff = nullptr;
	MusicLoad *musicLoad = nullptr;

public:
	FavoriteItem( MusicCentreWidget *music_centre_widget, const QString &favorite_item_name );
	~FavoriteItem( ) override;
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;
	virtual const QString & getFavoriteItemName( ) const;

protected:
	virtual bool unsafetySetMusicItemInfoVector( const std::vector< MusicItem * > &music_items );

	virtual bool unsafetyClearInfo( );
	virtual bool unsafetyClearShow( );
	virtual bool unsafetyUpdateInfo( );
	virtual bool unsafetyUpdateShow( );
	virtual bool unsafetyWidgetRepaint( );
	virtual bool unsafetyWidgetUpdate( );
	virtual bool unsafetyUpdate( );

	virtual void unsafetyClear( );
	virtual bool unsafetyUpdateMusicItem( MusicItem *music_item );
	virtual bool unsafetyRemoveMusicItem( MusicItem *music_item );
	virtual bool unsafetyHasMusicItem( size_t &result_index, const MusicItem *music_item ) const;
	virtual bool unsafetyAddMusicItem( MusicItem *music_item );

	virtual bool renderImage( QPainter &painter, int intervalWidth, size_t index, MusicItem *music_item, int calculate_min_width, int calculate_height, const QFont &font, const QColor &fill_separator_color ) const;
	virtual bool renderImage( size_t index, MusicItem *music_item ) const;

public:
	virtual bool hasMusicFile( const QString &file_path ) const;
	virtual bool updateMusicItem( MusicItem *music_item );
	virtual bool removeMusicItem( MusicItem *music_item );
	virtual bool hasMusicItem( size_t &result_index, const MusicItem *music_item ) const;
	virtual bool addMusicItem( MusicItem *music_item );
	virtual void clear( );
	virtual bool setMusicItemInfoVector( const std::vector< MusicItem * > &music_items );
	virtual void getMusicItemVector( std::vector< MusicItem * > &result_music_item_vector );
	virtual void getMusicItemVector( size_t &result_count, std::vector< MusicItem * > &result_music_item_vector, const std::vector< size_t > &get_index );
	virtual QImage * getDrawBuff( ) const;
	virtual void updateItemWidthInfo( MusicTitleWidget *music_title_widget, int interval_width, int separator_width, int music_code_width, int music_name_width, int music_singer_name_width, int music_duration_time_width );
	virtual bool removeMusicLoad( MusicLoad *music_load );
	virtual MusicLoad * getMusicLoad( ) const;
	virtual size_t loadMusicFile( const std::vector< QString > &music_file_path_vector );
	virtual size_t loadMusicFile( const std::list< QString > &music_file_path_list );
	virtual size_t loadMusicFile( const QStringList &music_file_path_list );
	virtual size_t loadMusicFile( const QString &music_file_path );
	virtual bool loadMusicDir( const QString &music_dir_path );
	virtual bool repaint( );
	virtual bool update( );
	virtual bool updateInfo( );
	virtual bool updateShow( );
	virtual bool widgetRepaint( );
	virtual bool widgetUpdate( );
};

#endif // FAVORITEITEM_H_H_HEAD__FILE__
