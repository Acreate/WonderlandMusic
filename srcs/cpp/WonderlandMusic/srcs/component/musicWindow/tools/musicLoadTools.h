#ifndef MUSICLOADTOOLS_H_H_HEAD__FILE__
#define MUSICLOADTOOLS_H_H_HEAD__FILE__
class QString;
class MusicFavoriteWidget;
class MusicCentreWidget;
class MusicLoad;
class FavoriteItem;

class MusicLoadTools {
	friend class FavoriteItem;
	friend class MusicItem;
	static bool createMusicLoad( MusicLoad **music_load, FavoriteItem *favorite_item );
	static bool releaseMusicLoad( MusicLoad **music_load );
	static bool setMusicListWidget( MusicLoad *music_load, FavoriteItem *favorite_item );
	static bool removeMusicItemsHistory( MusicLoad *music_load, const MusicItem *music_item );
	static bool hasMusicLoadMusicFileHistory( MusicLoad *music_load, const QString &music_file );
};
#endif // MUSICLOADTOOLS_H_H_HEAD__FILE__
