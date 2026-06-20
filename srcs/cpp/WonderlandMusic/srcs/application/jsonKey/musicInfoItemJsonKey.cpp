#include "musicInfoItemJsonKey.h"

bool MusicInfoItemJsonKey::init( ) {
	musicInfoFile = "music.file";
	musicInfoName = "music.name";
	musicInfoSinger = "music.singer";
	musicInfoDuration = "music.duartion";
	return true;
}

const QString & MusicInfoItemJsonKey::getMusicInfoFile( ) const {
	return musicInfoFile;
}

const QString & MusicInfoItemJsonKey::getMusicInfoName( ) const {
	return musicInfoName;
}

const QString & MusicInfoItemJsonKey::getMusicInfoSinger( ) const {
	return musicInfoSinger;
}

const QString & MusicInfoItemJsonKey::getMusicInfoDuration( ) const {
	return musicInfoDuration;
}
