#include "musicItemJsonKey.h"

bool MusicItemJsonKey::init( ) {
	musicVector = "music.vector";
	musicData = "music.data";
	musicCount = "music.count";
	return true;
}

const QString & MusicItemJsonKey::getMusicVector( ) const {
	return musicVector;
}

const QString & MusicItemJsonKey::getMusicData( ) const {
	return musicData;
}

const QString & MusicItemJsonKey::getMusicCount( ) const {
	return musicCount;
}
