#include "musicItemWidthInfoJsonKey.h"

bool MusicItemWidthInfoJsonKey::init( ) {
	suggestHeight = QObject::tr( "suggest.height" );
	musicCodeWidth = QObject::tr( "music.code.width" );
	musicNameWidth = QObject::tr( "music.name.width" );
	musicSingerNameWidth = QObject::tr( "music.singer.name.width" );
	musicDurationTimeWidth = QObject::tr( "music.duration.time.width" );

	return true;
}
const QString & MusicItemWidthInfoJsonKey::getSuggestHeight( ) const {
	return suggestHeight;
}

const QString & MusicItemWidthInfoJsonKey::getMusicCodeWidth( ) const {
	return musicCodeWidth;
}
const QString & MusicItemWidthInfoJsonKey::getMusicNameWidth( ) const {
	return musicNameWidth;
}
const QString & MusicItemWidthInfoJsonKey::getMusicSingerNameWidth( ) const {
	return musicSingerNameWidth;
}
const QString & MusicItemWidthInfoJsonKey::getMusicDurationTimeWidth( ) const {
	return musicDurationTimeWidth;
}
