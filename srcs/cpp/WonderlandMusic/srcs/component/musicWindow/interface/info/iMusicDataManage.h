#ifndef IMUSICDATAMANAGE_H_H_HEAD__FILE__
#define IMUSICDATAMANAGE_H_H_HEAD__FILE__
#include "../musicCentreWidgetChild/iMusicCentreWidgetChild.h"

class IMusicItem;
class QPainter;
class IMusicFavoriteItem;

class IMusicDataManage : public IMusicCentreWidgetChild {
protected:
	~IMusicDataManage( ) override;

public:
	virtual bool setCurrentSelectFavoriteItem( IMusicFavoriteItem *set_select_music_favorite_item ) = 0;
	virtual bool getCurrentSelectFavoriteItem( IMusicFavoriteItem *&result_current_select_music_favorite_item ) const = 0;
	virtual bool getMusicFavoriteItem( IMusicFavoriteItem *&result_default_music_favorite_item, std::vector< IMusicFavoriteItem * > &result_music_favorite_item ) const = 0;
	virtual bool getMusicFavoriteItem( std::vector< IMusicFavoriteItem * > &result_music_favorite_item ) const = 0;
	virtual bool getMusicFavoriteItem( IMusicFavoriteItem *&result_default_music_favorite_item ) const = 0;
	virtual bool initDefaultMusicFavoriteItem( ) = 0;
	virtual bool clear( ) = 0;
};

#endif // IMUSICDATAMANAGE_H_H_HEAD__FILE__
