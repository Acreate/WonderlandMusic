#include "musicLoadTools.h"

#include "../musicLoad/musicLoad.h"

bool MusicLoadTools::createMusicLoad( MusicLoad **music_load, FavoriteItem *favorite_item ) {
	*music_load = new MusicLoad( favorite_item );
	return *music_load;
}
bool MusicLoadTools::releaseMusicLoad( MusicLoad **music_load ) {
	delete *music_load;
	*music_load = nullptr;
	return true;
}
bool MusicLoadTools::setMusicListWidget( MusicLoad *music_load, FavoriteItem *favorite_item ) {
	music_load->favoriteItem = favorite_item;
	return true;
}
bool MusicLoadTools::removeMusicItemsHistory( MusicLoad *music_load, const MusicItem *music_item ) {
	return music_load->removeMusicItemsHistory( music_item );
}
bool MusicLoadTools::hasMusicLoadMusicFileHistory( MusicLoad *music_load, const QString &music_file ) {
	return music_load->hasMusicLoadMusicFileHistory( music_file );
}
