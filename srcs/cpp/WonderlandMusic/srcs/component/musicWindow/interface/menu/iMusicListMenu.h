#ifndef IMUSICLISTMENU_H_H_HEAD__FILE__
#define IMUSICLISTMENU_H_H_HEAD__FILE__

#include <interface/iAppJsonData.h>

#include "../../../../interface/iAppResourceCore.h"

#include "../musicWidgetChild/musicWidgetChild.h"

class IMusicItem;
class IMusicListWidget;
class MusicCentreWidget;
class QMenu;

class IMusicListMenu : public MusicWidgetChild, public IAppResourceCore {
	friend class MusicCentreWidget;

public:
	IMusicListMenu( );
	~IMusicListMenu( ) override;

protected:
	virtual bool execMenu( IMusicListWidget *music_list_widget, IMusicItem *music_item, const QPoint &mouse_global_point ) = 0;

public:
	virtual QMenu * toMenu( ) = 0;
};

#endif // IMUSICLISTMENU_H_H_HEAD__FILE__
