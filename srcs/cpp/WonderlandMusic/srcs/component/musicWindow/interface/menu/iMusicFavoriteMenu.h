#ifndef IMUSICFAVORITEMENU_H_H_HEAD__FILE__
#define IMUSICFAVORITEMENU_H_H_HEAD__FILE__

#include <interface/iAppCore.h>

#include <interface/iAppJsonData.h>

class QMenu;
class FavoriteItem;
class MusicFavoriteWidget;

class IMusicFavoriteMenu : public IAppCore, public IAppJsonData {
	friend class MusicFavoriteWidget;

public:
	IMusicFavoriteMenu( );
	~IMusicFavoriteMenu( ) override;

protected:
	virtual bool execMenu( MusicFavoriteWidget *music_favorite_widget, FavoriteItem *favorite_item, const QPoint &mouse_global_point ) = 0;

public:
	virtual QMenu * toMenu( ) = 0;
};

#endif // IMUSICFAVORITEMENU_H_H_HEAD__FILE__
