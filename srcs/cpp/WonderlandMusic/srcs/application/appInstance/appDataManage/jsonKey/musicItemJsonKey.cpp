#include "musicItemJsonKey.h"
bool MusicItemJsonKey::init( ) {
	idCodeKey = "id";
	nameKey = "name";
	singerKey = "singer";
	absoluteFilePathKey = "file";
	elapsedTimeKey = "time";
	return true;
}
const QString & MusicItemJsonKey::getIdCodeKey( ) const {
	return idCodeKey;
}
const QString & MusicItemJsonKey::getNameKey( ) const {
	return nameKey;
}
const QString & MusicItemJsonKey::getSingerKey( ) const {
	return singerKey;
}
const QString & MusicItemJsonKey::getAbsoluteFilePathKey( ) const {
	return absoluteFilePathKey;
}
const QString & MusicItemJsonKey::getElapsedTimeKey( ) const {
	return elapsedTimeKey;
}
