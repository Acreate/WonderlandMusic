#include "musicLoadTools.h"

#include "../musicLoad/musicLoad.h"

bool MusicLoadTools::createMusicLoad( MusicLoad **music_load, FavoriteItem *favorite_item ) {
	if( favorite_item == nullptr )
		return false;
	*music_load = new MusicLoad( favorite_item );
	return *music_load;
}
bool MusicLoadTools::releaseMusicLoad( MusicLoad **music_load ) {
	if( *music_load == nullptr )
		return false;
	delete *music_load;
	*music_load = nullptr;
	return true;
}
bool MusicLoadTools::setMusicListWidget( MusicLoad *music_load, FavoriteItem *favorite_item ) {
	if( music_load == nullptr )
		return false;
	music_load->favoriteItem = favorite_item;
	return true;
}
