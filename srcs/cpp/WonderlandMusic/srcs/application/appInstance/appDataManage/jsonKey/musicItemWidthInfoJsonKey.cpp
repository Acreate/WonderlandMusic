#include "musicItemWidthInfoJsonKey.h"

bool MusicItemWidthInfoJsonKey::init( ) {
	suggestHeight = QObject::tr( "suggest.height" );
	clickWidth = QObject::tr( "click.width" );
	intervalWidth = QObject::tr( "interval.width" );
	separatorWidth = QObject::tr( "separator.width" );
	musicCodeWidth = QObject::tr( "music.code.width" );
	musicNameWidth = QObject::tr( "music.name.width" );
	musicSingerNameWidth = QObject::tr( "music.singer.name.width" );
	musicDurationTimeWidth = QObject::tr( "music.duration.time.width" );
	minItemWidth = QObject::tr( "min.item.width" );

	return true;
}
const QString & MusicItemWidthInfoJsonKey::getSuggestHeight( ) const {
	return suggestHeight;
}
const QString & MusicItemWidthInfoJsonKey::getClickWidth( ) const {
	return clickWidth;
}
const QString & MusicItemWidthInfoJsonKey::getIntervalWidth( ) const {
	return intervalWidth;
}
const QString & MusicItemWidthInfoJsonKey::getSeparatorWidth( ) const {
	return separatorWidth;
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
const QString & MusicItemWidthInfoJsonKey::getMinItemWidth( ) const {
	return minItemWidth;
}
