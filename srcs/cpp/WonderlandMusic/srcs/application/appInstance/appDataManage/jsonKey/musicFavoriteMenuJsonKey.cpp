#include "musicFavoriteMenuJsonKey.h"

bool MusicFavoriteMenuJsonKey::init( ) {
	loadMultDir = "menu.music.favorite.load.mult.dir.path";
	loadMultFile = "menu.music.favorite.load.mult.file.path";
	return true;
}
const QString & MusicFavoriteMenuJsonKey::getLoadMultDir( ) const {
	return loadMultDir;
}
const QString & MusicFavoriteMenuJsonKey::getLoadMultFile( ) const {
	return loadMultFile;
}
