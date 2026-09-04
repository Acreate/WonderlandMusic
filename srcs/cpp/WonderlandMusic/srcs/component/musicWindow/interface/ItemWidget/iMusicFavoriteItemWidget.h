#ifndef IMUSICFAVORITEITEMWIDGET_H_H_HEAD__FILE__
#define IMUSICFAVORITEITEMWIDGET_H_H_HEAD__FILE__

#include "../musicCentreWidgetChild/iMusicCentreWidgetChild.h"

class IMusicFavoriteItem;
class IMusicFavoriteWidget;
class QMouseEvent;

class IMusicFavoriteItemWidget : public IMusicCentreWidgetChild {
protected:
	~IMusicFavoriteItemWidget( ) override;

public:
	IMusicFavoriteItemWidget( );
	virtual bool bindMusicFavoriteItem( IMusicFavoriteItem *music_favorite_item ) = 0;
	virtual bool setMusicFavoriteWidget( IMusicFavoriteWidget *music_favorite_widget ) = 0;
	virtual bool updateLayout( ) =0;
	virtual IMusicFavoriteItem * getBindMusicFavoriteItem( ) const = 0;
	virtual bool getGeometry( QRect &result_geometry ) const;
	virtual bool setGeometry( const QRect &set_geometry );
	virtual bool setPos( const int &target_pos_x, const int &target_pos_y ) = 0;
	virtual bool setSize( const int &set_width, const int &set_height ) =0;
	virtual bool getPos( int &target_pos_x, int &target_pos_y ) const = 0;
	virtual bool getSize( int &result_width, int &result_height ) const = 0;
	virtual bool showItemWidget( ) = 0;
	virtual bool hideItemWidget( ) = 0;
};

#endif // IMUSICFAVORITEITEMWIDGET_H_H_HEAD__FILE__
