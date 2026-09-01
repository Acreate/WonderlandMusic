#ifndef IMUSICCENTREWIDGET_H_H_HEAD__FILE__
#define IMUSICCENTREWIDGET_H_H_HEAD__FILE__
#include <interface/iAppResourceCore.h>

#include <interface/iAppCore.h>

#include <interface/iAppJsonData.h>

class IMusicItem;
class IMusicFavoriteItem;
class IMusicWidgetSizeInfo;
class IMusicListMenu;
class IMusicFavoriteMenu;
class IMusicDataManage;
class IMusicTitleWidget;
class IMusicListWidget;
class IMusicFavoriteWidget;
class MusicWindow;

class IMusicCentreWidget : public IAppCore, public IAppJsonData, public IAppResourceCore {
	friend class MusicWindow;

protected:
	virtual int setFavoriteWidth( const int &favoriet_width );
	virtual int setTitleHeight( const int &title_height );
	virtual bool setMusicWindow( MusicWindow *music_window ) =0;
	virtual bool execMenu( IMusicFavoriteWidget *music_favorite_widget, IMusicFavoriteItem *favorite_item, const QPoint &mouse_global_point );
	virtual bool execMenu( IMusicListWidget *music_list_widget, IMusicItem *music_item, const QPoint &mouse_global_point );

public:
	IMusicCentreWidget( );
	virtual MusicWindow * getMusicWindow( ) const = 0;
	virtual IMusicFavoriteWidget * getMusicFavoriteWidget( ) const = 0;
	virtual IMusicListWidget * getMusicListWidget( ) const = 0;
	virtual IMusicTitleWidget * getMusicTitleWidget( ) const = 0;
	virtual IMusicDataManage * getMusicDataManage( ) const = 0;
	virtual IMusicFavoriteMenu * getMusicFavoriteMenu( ) const = 0;
	virtual IMusicListMenu * getMusicListMenu( ) const = 0;
	virtual IMusicWidgetSizeInfo * getMusicWidgetSizeInfo( ) const = 0;
	virtual IMusicFavoriteWidget * setMusicFavoriteWidget( IMusicFavoriteWidget *const music_favorite_widget ) = 0;
	virtual IMusicListWidget * setMusicListWidget( IMusicListWidget *const music_list_widget ) = 0;
	virtual IMusicTitleWidget * setMusicTitleWidget( IMusicTitleWidget *const music_title_widget ) = 0;
	virtual IMusicDataManage * setMusicDataManage( IMusicDataManage *const music_data_manage ) = 0;

	virtual IMusicFavoriteWidget * removeMusicFavoriteWidget( IMusicFavoriteWidget *const music_favorite_widget ) = 0;
	virtual IMusicListWidget * removeMusicListWidget( IMusicListWidget *const music_list_widget ) = 0;
	virtual IMusicTitleWidget * removeMusicTitleWidget( IMusicTitleWidget *const music_title_widget ) = 0;

	virtual bool repaintListWidget( ) = 0;
	virtual bool repaintTitleWidget( ) = 0;
	virtual bool repaintFavoriteWidget( ) = 0;
	virtual bool repaintMusicCentreWidget( ) = 0;
	virtual bool synchronizationChildrenWidgetSize( ) = 0;
	virtual QWidget * toWidget( ) = 0;
};

#endif // IMUSICCENTREWIDGET_H_H_HEAD__FILE__
