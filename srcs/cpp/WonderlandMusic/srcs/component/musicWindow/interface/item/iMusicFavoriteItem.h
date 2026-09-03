#ifndef IMUSICFAVORITEITEM_H_H_HEAD__FILE__
#define IMUSICFAVORITEITEM_H_H_HEAD__FILE__
#include "../musicCentreWidgetChild/iMusicCentreWidgetChild.h"

class IMusicFavoriteItemWidget;
class IMusicItem;
class QString;
class QImage;

class IMusicFavoriteItem : public IMusicCentreWidgetChild {
protected:
	static bool bindMusicFavoriteItem( IMusicFavoriteItemWidget *bind_target, IMusicFavoriteItem *bind_source );

	static bool setMusicItemFavoriteItem( IMusicItem *music_item, IMusicFavoriteItem *music_favorite_item );

public:
	IMusicFavoriteItem( );
	virtual bool getName( QString &result_name ) const = 0;
	virtual bool addMusicItem( IMusicItem *music_item ) = 0;
	virtual bool addMusicItem( const std::vector< IMusicItem * > &music_info_items ) = 0;
	virtual bool removeMusicItem( IMusicItem *music_item ) = 0;
	virtual bool clear( ) = 0;
	virtual bool update( ) = 0;
	virtual bool fromYPosGetMusicItem( IMusicItem *&result_music_item, const size_t &y_pos ) const =0;
	virtual bool fromIndexGetMusicItem( IMusicItem * &result_music_item_vector, const size_t &result_count ) const = 0;
	virtual bool fromMusicItemGetIndex( size_t &result_index, const IMusicItem *music_item ) const = 0;
	virtual bool fromNameGetFirstMusicItem( IMusicItem * &result_music_item, const QString &music_name ) const = 0;
	virtual bool fromFileBaseNameGetFirstMusicItem( IMusicItem * &result_music_item, const QString &file_base_name ) const = 0;
	virtual bool fromFileAbsPathGetFirstMusicItem( IMusicItem * &result_music_item, const QString &path ) const = 0;
	virtual bool fromSingerGetFirstMusicItem( IMusicItem * &result_music_item, const QString &singer ) const = 0;
	virtual size_t getMusicVectorClone( std::vector< IMusicItem * > &result_clone_vector ) const = 0;
	virtual IMusicFavoriteItemWidget * getMusicFavoriteItemWidget( ) const = 0;
	virtual bool loadMusicDirPath( const std::vector< QString > &music_file_path ) = 0;
	virtual bool loadMusicFile( const std::vector< QString > &music_file_path ) = 0;
	virtual bool loadMusicFile( const QString &music_file_path ) = 0;
};

#endif // IMUSICFAVORITEITEM_H_H_HEAD__FILE__
