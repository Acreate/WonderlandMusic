#include "musicWindowJsonKey.h"

#include "../../tools/pathInfoTools.h"
bool MusicWindowJsonKey::init( ) {
	jsonFilePath = "/json/app.data.music.json";
	return true;
}
QString MusicWindowJsonKey::getJsonFilePath( ) const {
	QString applicationDirPath;
	if( PathInfoTools::getAppSettintHomePath( applicationDirPath ) )
		return applicationDirPath + jsonFilePath;
	return applicationDirPath + jsonFilePath;
}
