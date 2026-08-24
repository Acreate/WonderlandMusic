#ifndef IMUSICFAVORITEITEMWIDGET_H_H_HEAD__FILE__
#define IMUSICFAVORITEITEMWIDGET_H_H_HEAD__FILE__
#include "../musicCentreWidgetChild/iMusicCentreWidgetChild.h"

class QMouseEvent;

class IMusicFavoriteItemWidget : public IMusicCentreWidgetChild {
	friend class IMusicFavoriteItem;

protected:
	virtual bool setBindMusicFavoriteItem( IMusicFavoriteItem *music_favorite_item ) =0;

public:
	IMusicFavoriteItemWidget( );
	~IMusicFavoriteItemWidget( ) override;
	virtual bool mousePress( const QMouseEvent &mouse_event ) const = 0;
	virtual bool mouseRelease( const QMouseEvent &mouse_event ) const = 0;
	virtual bool drawWidget( ) =0;
	virtual IMusicFavoriteItem * getBindMusicFavoriteItem( ) const =0;
};

#endif // IMUSICFAVORITEITEMWIDGET_H_H_HEAD__FILE__
