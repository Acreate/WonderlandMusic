#include "musicInfoItemWidgetJsonKey.h"

bool MusicInfoItemWidgetJsonKey::init( ) {
	musicInfoFile = "music.file";
	musicInfoName = "music.name";
	musicInfoSinger = "music.singer";
	musicInfoDuration = "music.duartion";
	return true;
}

const QString & MusicInfoItemWidgetJsonKey::getMusicInfoFile( ) const {
	return musicInfoFile;
}

const QString & MusicInfoItemWidgetJsonKey::getMusicInfoName( ) const {
	return musicInfoName;
}

const QString & MusicInfoItemWidgetJsonKey::getMusicInfoSinger( ) const {
	return musicInfoSinger;
}

const QString & MusicInfoItemWidgetJsonKey::getMusicInfoDuration( ) const {
	return musicInfoDuration;
}
