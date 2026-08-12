#include "appTranslateTools.h"

#include <application/appTranslate.h>

#include <head/defininition_get_translate.h>

#include "../application/translate/aboutWidgetTranslate.h"
#include "../application/translate/appMusicManageTranslate.h"
#include "instanceTools.h"

#include "../application/translate/dateTimeFormatTranslate.h"
#include "../application/translate/deleteExceptionTranslate.h"
#include "../application/translate/jsonTranslate.h"
#include "../application/translate/mainWindowTranslate.h"
#include "../application/translate/messageTranslate.h"
#include "../application/translate/musicFavoriteMenuTranslate.h"
#include "../application/translate/musicItemTranslate.h"
#include "../application/translate/musicListMenuTranslate.h"
#include "../application/translate/musicTitleWidgetTranslate.h"
#include "../application/translate/musicWindowTranslate.h"
#include "../application/translate/settingWidgetTranslate.h"
#include "../application/translate/stringEditorWidgetTranslate.h"
#include "../application/translate/systemTrayIconMenuTranslate.h"
#include "../application/translate/systemTrayIconTranslate.h"
#include "../application/translate/userMutexTranslate.h"
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
