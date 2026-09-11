#ifndef IMUSICFAVORITEMENU_H_H_HEAD__FILE__
#define IMUSICFAVORITEMENU_H_H_HEAD__FILE__

#include <interface/iAppResourceCore.h>

#include "../musicWidgetChild/musicWidgetChild.h"

class IMusicFavoriteItem;
class IMusicFavoriteWidget;
class IMusicCentreWidget;
class QMenu;

class IMusicFavoriteMenu : public MusicWidgetChild, public IAppResourceCore {
public:
	IMusicFavoriteMenu( );

protected:
	~IMusicFavoriteMenu( ) override;

public:
	virtual bool execMenu( IMusicFavoriteWidget *music_favorite_widget, IMusicFavoriteItem *favorite_item, const QPoint &mouse_global_point ) = 0;
	virtual QMenu * toMenu( ) = 0;
};

#endif // IMUSICFAVORITEMENU_H_H_HEAD__FILE__
