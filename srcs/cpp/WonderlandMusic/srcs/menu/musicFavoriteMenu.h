#ifndef MUSICFAVORITEMENU_H_H_HEAD__FILE__
#define MUSICFAVORITEMENU_H_H_HEAD__FILE__

#include <QMenu>

#include "../component/musicWindow/interface/menu/iMusicFavoriteMenu.h"

class MusicFavoriteMenu : public QMenu, public IMusicFavoriteMenu {
	Q_OBJECT;

protected:
	MusicFavoriteWidget *musicFavoriteWidget = nullptr;
	FavoriteItem *oldFavoriteItem = nullptr;
	FavoriteItem *favoriteItem = nullptr;
	QAction *createFavoriteItemAction = nullptr;
	QAction *renameFavoriteItemAction = nullptr;
	QAction *deleteFavoriteItemAction = nullptr;
	QAction *addMusicFileAction = nullptr;
	QAction *addMusicDirAction = nullptr;

	QString openSelecteMultiFileWidgetPath;
	QString openSelecteMultiDirWidgetPath;

public:
	MusicFavoriteMenu( );
	~MusicFavoriteMenu( ) override;

protected:
	bool deleteResource( ) override;

public:
	bool initBefore( ) override;
	bool init( ) override;
	bool initAfter( ) override;
	bool getJsonData( QJsonObject &get_json_object ) const override;
	bool setJsonData( const QJsonObject &set_json_object ) override;

protected:
	bool execMenu( MusicFavoriteWidget *music_favorite_widget, FavoriteItem *favorite_item, const QPoint &mouse_global_point ) override;
	void hideEvent( QHideEvent * ) override;

private Q_SLOTS :
	void slot_createFavoriteItem( );
	void slot_renameFavoriteItem( );
	void slot_deleteFavoriteItem( );
	void slot_addMusicFile( );
	void slot_addMusicDir( );

public:
	QMenu * toMenu( ) override;
};

#endif // MUSICFAVORITEMENU_H_H_HEAD__FILE__
