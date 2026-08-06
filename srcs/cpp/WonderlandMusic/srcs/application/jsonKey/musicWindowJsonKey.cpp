#include "musicWindowJsonKey.h"

#include "../appDataJsonKey.h"
#include "../appDataManage.h"
#include "../appInstance.h"

#include "../../head/defininition_get_json_key.h"

#include "../../tools/appJsonKeyTools.h"
Defininition_Get_Json_Key( MusicWindow );
bool MusicWindowJsonKey::init( ) {
	jsonFilePath = "/json/app.data.music.json";
	return true;
}
QString MusicWindowJsonKey::getJsonFilePath( ) const {
	auto appInstance = AppInstance::getAppInstance( );
	auto applicationDirPath = appInstance->getAppDataManage( )->getAppSettingPath( );
	return applicationDirPath + jsonFilePath;
}
