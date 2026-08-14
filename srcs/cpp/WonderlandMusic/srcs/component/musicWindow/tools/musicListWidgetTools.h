#ifndef MUSICLISTWIDGETTOOLS_H_H_HEAD__FILE__
#define MUSICLISTWIDGETTOOLS_H_H_HEAD__FILE__

class ItemWidthInfo;
class IMusicListMenu;
class MusicTitleWidget;
class MusicListWidget;
class MusicFavoriteWidget;
class FavoriteItem;

class MusicListWidgetTools {
private:
	friend class MusicCentreWidget;
	friend class MusicFavoriteWidget;
	static void updateItemWidthInfo( MusicListWidget *targetr, const ItemWidthInfo &item_width_info );
	static bool setMusicListMenu( MusicListWidget *targetr, IMusicListMenu *music_list_menu );
};

#endif // MUSICLISTWIDGETTOOLS_H_H_HEAD__FILE__
