#include "appTranslateTools.h"


#include <head/defininition_get_translate.h>

#include "instanceTools.h"

#include "../application/appInstance/appDataManage/appTranslate.h"
#include "../application/appInstance/appDataManage/translate/aboutWidgetTranslate.h"
#include "../application/appInstance/appDataManage/translate/appMusicManageTranslate.h"
#include "../application/appInstance/appDataManage/translate/dateTimeFormatTranslate.h"
#include "../application/appInstance/appDataManage/translate/deleteExceptionTranslate.h"
#include "../application/appInstance/appDataManage/translate/jsonTranslate.h"
#include "../application/appInstance/appDataManage/translate/mainWindowTranslate.h"
#include "../application/appInstance/appDataManage/translate/messageTranslate.h"
#include "../application/appInstance/appDataManage/translate/musicFavoriteMenuTranslate.h"
#include "../application/appInstance/appDataManage/translate/musicItemTranslate.h"
#include "../application/appInstance/appDataManage/translate/musicListMenuTranslate.h"
#include "../application/appInstance/appDataManage/translate/musicTitleWidgetTranslate.h"
#include "../application/appInstance/appDataManage/translate/musicWindowTranslate.h"
#include "../application/appInstance/appDataManage/translate/settingWidgetTranslate.h"
#include "../application/appInstance/appDataManage/translate/stringEditorWidgetTranslate.h"
#include "../application/appInstance/appDataManage/translate/systemTrayIconMenuTranslate.h"
#include "../application/appInstance/appDataManage/translate/systemTrayIconTranslate.h"
#include "../application/appInstance/appDataManage/translate/userMutexTranslate.h"

AppTranslate * AppTranslateTools::getAppTranslate( ) {
	return InstanceTools::getAppTranslate( );
}

Defininition_Get_Translate( AboutWidget );

Defininition_Get_Translate( AppMusicManage );

Defininition_Get_Translate( DateTimeFormat );

Defininition_Get_Translate( DeleteException );

Defininition_Get_Translate( Json );

Defininition_Get_Translate( MainWindow );

Defininition_Get_Translate( Message );

Defininition_Get_Translate( MusicFavoriteMenu );

Defininition_Get_Translate( MusicListMenu );

Defininition_Get_Translate( MusicTitleWidget );

Defininition_Get_Translate( MusicWindow );

Defininition_Get_Translate( SettingWidget );

Defininition_Get_Translate( SystemTrayIconMenu );

Defininition_Get_Translate( SystemTrayIcon );

Defininition_Get_Translate( UserMutex );
Defininition_Get_Translate( StringEditorWidget );
Defininition_Get_Translate( MusicItem );
