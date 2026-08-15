#include "appJsonKeyTools.h"

#include <head/defininition_get_json_key.h>
#include "instanceTools.h"

#include "../application/appInstance/appDataManage/appDataJsonKey.h"
#include "../application/appInstance/appDataManage/jsonKey/aboutWidgetJsonKey.h"
#include "../application/appInstance/appDataManage/jsonKey/appDataManageJsonKey.h"
#include "../application/appInstance/appDataManage/jsonKey/appMenuManageJsonKey.h"
#include "../application/appInstance/appDataManage/jsonKey/appMusicManageJsonKey.h"
#include "../application/appInstance/appDataManage/jsonKey/appUserInterfaceManageJsonKey.h"
#include "../application/appInstance/appDataManage/jsonKey/mainWindowJsonKey.h"
#include "../application/appInstance/appDataManage/jsonKey/musicFavoriteMenuJsonKey.h"
#include "../application/appInstance/appDataManage/jsonKey/musicListMenuJsonKey.h"
#include "../application/appInstance/appDataManage/jsonKey/musicWindowJsonKey.h"
#include "../application/appInstance/appDataManage/jsonKey/systemTrayIconJsonKey.h"

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
Defininition_Get_Json_Key( MusicFavoriteMenu );
Defininition_Get_Json_Key( MusicListMenu );
Defininition_Get_Json_Key( AppMenuManage );
