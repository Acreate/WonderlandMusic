#include "appJsonKeyTools.h"

#include <head/defininition_get_json_key.h>
#include "instanceTools.h"

#include "../application/appDataJsonKey.h"
#include "../application/jsonKey/aboutWidgetJsonKey.h"
#include "../application/jsonKey/appDataManageJsonKey.h"
#include "../application/jsonKey/appMusicManageJsonKey.h"
#include "../application/jsonKey/appUserInterfaceManageJsonKey.h"
#include "../application/jsonKey/mainWindowJsonKey.h"
#include "../application/jsonKey/musicWindowJsonKey.h"
#include "../application/jsonKey/systemTrayIconJsonKey.h"
AppDataJsonKey * AppJsonKeyTools::getAppJsonKey( ) {
	return InstanceTools::getAppDataJsonKey( );
}

Defininition_Get_Json_Key( AboutWidget );

Defininition_Get_Json_Key( AppDataManage );

Defininition_Get_Json_Key( AppMusicManage );
Defininition_Get_Json_Key( AppUserInterfaceManage );

Defininition_Get_Json_Key( SystemTrayIcon );
Defininition_Get_Json_Key( MainWindow );
Defininition_Get_Json_Key( MusicWindow );
