#ifndef MUSICFAVORITEWIDGETTOOLS_H_H_HEAD__FILE__
#define MUSICFAVORITEWIDGETTOOLS_H_H_HEAD__FILE__

class IMusicFavoriteMenu;
class MusicFavoriteWidget;

class MusicFavoriteWidgetTools {
	friend class MusicCentreWidget;
	static bool setMusicFavoriteMenu( MusicFavoriteWidget *music_favorite_widget, IMusicFavoriteMenu *music_favorite_menu );
};

#endif // MUSICFAVORITEWIDGETTOOLS_H_H_HEAD__FILE__
