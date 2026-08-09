#ifndef IMUSICLISTMENU_H_H_HEAD__FILE__
#define IMUSICLISTMENU_H_H_HEAD__FILE__
#include <QMenu>

#include <interface/iAppCore.h>

class MusicItem;

class IMusicListMenu : public IAppCore {
	friend class MusicListWidget;

public:
	IMusicListMenu( );
	~IMusicListMenu( ) override;

protected:
	virtual bool execMenu( MusicListWidget *music_list_widget, MusicItem *music_item, const QPoint &mouse_global_point ) = 0;
};

#endif // IMUSICLISTMENU_H_H_HEAD__FILE__
