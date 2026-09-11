#ifndef IMUSICLISTMENU_H_H_HEAD__FILE__
#define IMUSICLISTMENU_H_H_HEAD__FILE__

#include <interface/iAppResourceCore.h>

#include "../musicWidgetChild/musicWidgetChild.h"

class IMusicItem;
class IMusicListWidget;
class MusicCentreWidget;
class QMenu;

class IMusicListMenu : public MusicWidgetChild, public IAppResourceCore {
public:
	IMusicListMenu( );

protected:
	~IMusicListMenu( ) override;

public:
	virtual bool execMenu( IMusicListWidget *music_list_widget, IMusicItem *music_item, const QPoint &mouse_global_point ) = 0;
	virtual QMenu * toMenu( ) = 0;
};

#endif // IMUSICLISTMENU_H_H_HEAD__FILE__
