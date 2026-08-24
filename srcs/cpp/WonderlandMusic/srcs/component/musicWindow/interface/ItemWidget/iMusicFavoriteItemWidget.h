#ifndef IMUSICFAVORITEITEMWIDGET_H_H_HEAD__FILE__
#define IMUSICFAVORITEITEMWIDGET_H_H_HEAD__FILE__
#include "../musicCentreWidgetChild/iMusicCentreWidgetChild.h"

class IMusicFavoriteWidget;
class QMouseEvent;

class IMusicFavoriteItemWidget : public IMusicCentreWidgetChild {
	friend class IMusicFavoriteItem;
	friend class IMusicFavoriteWidget;
	friend class MusicCentreWidget;

protected:
	virtual bool bindMusicFavoriteItem( IMusicFavoriteItem *music_favorite_item ) = 0;

public:
	IMusicFavoriteItemWidget( );
	~IMusicFavoriteItemWidget( ) override;
	virtual bool setMusicFavoriteWidget( IMusicFavoriteWidget *music_favorite_widget ) = 0;
	virtual bool updateLayout( ) =0;
	virtual IMusicFavoriteItem * getBindMusicFavoriteItem( ) const = 0;
};

#endif // IMUSICFAVORITEITEMWIDGET_H_H_HEAD__FILE__
