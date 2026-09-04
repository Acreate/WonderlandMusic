#ifndef APPDRAWMANAGE_H_H_HEAD__FILE__
#define APPDRAWMANAGE_H_H_HEAD__FILE__

#include <interface/iAppCore.h>

#include "../../../interface/iAppResourceCore.h"

class IMusicItemWidthInfo;
class IMusicItem;
class IMusicFavoriteItem;
class QPainter;
class AppRenderImage;

class AppDrawManage : public IAppCore, public IAppResourceCore {
protected:
	/// @brief 渲染对象
	AppRenderImage *appRenderImage = nullptr;

public:
	~AppDrawManage( ) override;

protected:
	bool deleteResource( ) override;

public:
	bool init( ) override;

	bool initBefore( ) override;

	bool initAfter( ) override;

	virtual AppRenderImage * getAppRenderImage( ) const;
	virtual bool drawTitle( QPainter &painter, const IMusicItemWidthInfo *music_item_width_info, int offset_pos_x, int offset_pos_y ) const;
	virtual bool drawItem( QPainter &painter, const IMusicFavoriteItem *music_favorite_item, const int &offset_pos_x, const int &offset_pos_y ) const;
	virtual bool drawItem( QPainter &painter, const IMusicFavoriteItem *music_favorite_item ) const;
	virtual bool drawItem( QPainter &painter, const IMusicItem *music_item, const int &offset_pos_x, const int &offset_pos_y ) const;
	virtual bool drawItem( QPainter &painter, const std::vector< IMusicItem * > &music_item_vector, const int &offset_pos_x, const int &offset_pos_y ) const;
	virtual bool drawItem( QPainter &painter, const IMusicItem *music_item ) const;
	virtual bool drawItem( QPainter &painter, const std::vector< IMusicItem * > &music_item_vector ) const;

	virtual bool drawItem( QPainter &painter, const IMusicItem *music_item, const IMusicItemWidthInfo *music_item_width_info ) const;
	virtual bool drawItem( QPainter &painter, const std::vector< IMusicItem * > &music_item_vector, const IMusicItemWidthInfo *music_item_width_info ) const;
	virtual bool drawItem( QPainter &painter, const IMusicItem *music_item, const IMusicItemWidthInfo *music_item_width_info, const int &pos_x, const int &pos_y ) const;
	virtual bool drawItem( QPainter &painter, const std::vector< IMusicItem * > &music_item_vector, const IMusicItemWidthInfo *music_item_width_info, const int &pos_x, const int &pos_y ) const;

	virtual bool drawItemBakground( QPainter &painter, IMusicItem *music_item );
	virtual bool drawItemBakground( QPainter &painter, IMusicItem *music_item, const IMusicItemWidthInfo *music_item_width_info );
	virtual bool drawItemBakground( QPainter &painter, IMusicItem *music_item, const IMusicItemWidthInfo *music_item_width_info, const int &pos_x, const int &pos_y );

	virtual bool drawItemBakground( QPainter &painter, const std::vector< IMusicItem * > &music_item_vector );
	virtual bool drawItemBakground( QPainter &painter, const std::vector< IMusicItem * > &music_item_vector, const IMusicItemWidthInfo *music_item_width_info );
	virtual bool drawItemBakground( QPainter &painter, const std::vector< IMusicItem * > &music_item_vector, const IMusicItemWidthInfo *music_item_width_info, const int &pos_x, const int &pos_y );
};

#endif // APPDRAWMANAGE_H_H_HEAD__FILE__
