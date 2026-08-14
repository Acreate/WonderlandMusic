#include "musicWindowJsonKey.h"

bool MusicWindowJsonKey::init( ) {
	filePath = "/json/app.data.music.json";
	musicCentreWidgetKey = "music.centre.widget.json";
	return true;
}
const QString & MusicWindowJsonKey::getMusicCentreWidgetKey( ) const {
	return musicCentreWidgetKey;
}
