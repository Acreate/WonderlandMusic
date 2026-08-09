#ifndef MUSICFAVORITEMENU_H_H_HEAD__FILE__
#define MUSICFAVORITEMENU_H_H_HEAD__FILE__

#include <QMenu>

#include "../component/musicWindow/interface/menu/iMusicFavoriteMenu.h"

class MusicFavoriteMenu : public QMenu, public IMusicFavoriteMenu {
	Q_OBJECT;

public:
	MusicFavoriteMenu( );
	~MusicFavoriteMenu( ) override;

protected:
	bool deleteResource( ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;

protected:
	bool execMenu( MusicFavoriteWidget *music_list_widget, FavoriteItem *favorite_item, const QPoint &mouse_global_point ) override;

public:
	QMenu * toMenu( ) override;
};

#endif // MUSICFAVORITEMENU_H_H_HEAD__FILE__
