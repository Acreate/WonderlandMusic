#ifndef MUSICLOADTOOLS_H_H_HEAD__FILE__
#define MUSICLOADTOOLS_H_H_HEAD__FILE__
class MusicFavoriteWidget;
class MusicCentreWidget;
class MusicLoad;
class FavoriteItem;

class MusicLoadTools {
	friend class FavoriteItem;
	static bool createMusicLoad( MusicLoad **music_load, FavoriteItem *favorite_item );
	static bool releaseMusicLoad( MusicLoad **music_load );
	static bool setMusicListWidget( MusicLoad *music_load, FavoriteItem *favorite_item );
};
#endif // MUSICLOADTOOLS_H_H_HEAD__FILE__
