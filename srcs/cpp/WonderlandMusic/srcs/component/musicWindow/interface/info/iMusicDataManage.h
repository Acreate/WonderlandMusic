#ifndef IMUSICDATAMANAGE_H_H_HEAD__FILE__
#define IMUSICDATAMANAGE_H_H_HEAD__FILE__
#include "../musicCentreWidgetChild/iMusicCentreWidgetChild.h"

class IMusicItem;
class QPainter;
class IMusicFavoriteItem;

class IMusicDataManage : public IMusicCentreWidgetChild {
public:
	virtual bool setCurrentSelectFavoriteItem( const IMusicFavoriteItem *set_select_music_favorite_item ) = 0;
	virtual bool getCurrentSelectFavoriteItem( IMusicFavoriteItem *&result_current_select_music_favorite_item ) const = 0;
	virtual bool getMusicFavoriteItem( IMusicFavoriteItem *&result_default_music_favorite_item, std::vector< IMusicFavoriteItem * > &result_music_favorite_item ) const = 0;
	virtual bool getDefaultMusicFavoriteItem( IMusicFavoriteItem *&result_default_music_favorite_item ) const = 0;
	virtual bool getIndexMusicFavoriteItem( IMusicFavoriteItem *&result_default_music_favorite_item, const size_t &index ) const = 0;
	virtual bool getPosYMusicFavoriteItem( IMusicFavoriteItem *&result_default_music_favorite_item, const size_t &pos_x ) const = 0;
	virtual bool getNameMusicFavoriteItem( IMusicFavoriteItem *&result_default_music_favorite_item, const QString &music_favorite_name ) const = 0;
	virtual size_t getMusicNameVector( QString &result_default_music_favorite_name, std::vector< QString > &result_music_favorite_name_vector ) const = 0;
	virtual size_t findMusicItemAtFavoriteItem( const IMusicItem *music_item, std::vector< IMusicFavoriteItem * > &result_find_favorite_vector ) const = 0;
	virtual size_t findNameAtMusicItem( const QString &music_name, std::vector< IMusicItem * > &result_find_music_vector ) const = 0;
	virtual size_t findSingerAtMusicItem( const QString &music_singer, std::vector< IMusicItem * > &result_find_music_vector ) const = 0;
	virtual size_t findFileAtMusicItem( const QString &file_path, std::vector< IMusicItem * > &result_find_music_vector ) const = 0;
	virtual bool initDefaultMusicFavoriteItem( ) = 0;
	virtual bool clear( ) = 0;
};

#endif // IMUSICDATAMANAGE_H_H_HEAD__FILE__
