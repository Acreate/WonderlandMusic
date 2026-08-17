#ifndef IMUSICFAVORITEMENU_H_H_HEAD__FILE__
#define IMUSICFAVORITEMENU_H_H_HEAD__FILE__

#include <interface/iAppJsonData.h>

#include "../musicWidgetChild/musicWidgetChild.h"

class IMusicFavoriteItem;
class IMusicFavoriteWidget;
class MusicCentreWidget;
class QMenu;

class IMusicFavoriteMenu : public MusicWidgetChild, public IAppJsonData {
	friend class MusicCentreWidget;

public:
	IMusicFavoriteMenu( );
	~IMusicFavoriteMenu( ) override;

protected:
	virtual bool execMenu( IMusicFavoriteWidget *music_favorite_widget, IMusicFavoriteItem *favorite_item, const QPoint &mouse_global_point ) = 0;

public:
	virtual QMenu * toMenu( ) = 0;
};

#endif // IMUSICFAVORITEMENU_H_H_HEAD__FILE__
