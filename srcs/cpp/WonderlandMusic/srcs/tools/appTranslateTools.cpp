#include "appTranslateTools.h"
#include "../application/appDataManage.h"
#include "../application/appInstance.h"
#include "../application/appTranslate.h"
#include "../application/translate/aboutWidgetTranslate.h"
#include "../application/translate/appMusicManageTranslate.h"
#include "../application/translate/dateTimeFormatTranslate.h"
#include "../application/translate/deleteExceptionTranslate.h"
#include "../application/translate/favoriteWidgetMenuTranslate.h"
#include "../application/translate/favoriteWidgetTranslate.h"
#include "../application/translate/jsonTranslate.h"
#include "../application/translate/mainWindowTranslate.h"
#include "../application/translate/messageTranslate.h"
#include "../application/translate/musicInfoItemTranslate.h"
#include "../application/translate/optionDockWidgetTranslate.h"
#include "../application/translate/playerListWidgetMenuTranslate.h"
#include "../application/translate/playerListWidgetTranslate.h"
#include "../application/translate/playerToolsWidgetTranslate.h"
#include "../application/translate/playerTopWidgetTranslate.h"
#include "../application/translate/playerWindowTranslate.h"
#include "../application/translate/settingWidgetTranslate.h"
#include "../application/translate/systemTrayIconMenuTranslate.h"
#include "../application/translate/systemTrayIconTranslate.h"
#include "../application/translate/userMutexTranslate.h"

AppTranslate * AppTranslateTools::getAppTranslate( ) {
	auto appInstance = AppInstance::getAppInstance( );
	if( appInstance == nullptr )
		return nullptr;
	auto dataManage = appInstance->getAppDataManage( );
	if( dataManage == nullptr )
		return nullptr;
	return dataManage->getTranslate( );;
}

#define Defininition_Get_Translate( type_name_ ) \
	bool AppTranslateTools::get##type_name_(const std::function< void( type_name_##Translate & translate) > &translate_fun_call){\
		type_name_##Translate *var = nullptr; \
		AppTranslate *appTranslate = getAppTranslate( ); \
		if( appTranslate ){ \
			var = appTranslate->get##type_name_( );\
			if( var ) { \
				translate_fun_call( *var ); \
				return true; \
			}\
		}\
		var = new type_name_##Translate; \
		if( var->init( ) ) { \
			translate_fun_call( *var ); \
			delete var; \
			return true; \
		} \
		return false;\
	}
Defininition_Get_Translate( SettingWidget );
Defininition_Get_Translate( PlayerToolsWidget );
Defininition_Get_Translate( PlayerListWidgetMenu );
Defininition_Get_Translate( PlayerTopWidget );
Defininition_Get_Translate( PlayerWindow );
Defininition_Get_Translate( Json );
Defininition_Get_Translate( DateTimeFormat );
Defininition_Get_Translate( AboutWidget );
Defininition_Get_Translate( MainWindow );
Defininition_Get_Translate( Message );
Defininition_Get_Translate( PlayerListWidget );
Defininition_Get_Translate( MusicInfoItem );
Defininition_Get_Translate( SystemTrayIconMenu );
Defininition_Get_Translate( SystemTrayIcon );
Defininition_Get_Translate( UserMutex );
Defininition_Get_Translate( FavoriteWidget );
Defininition_Get_Translate( OptionDockWidget );
Defininition_Get_Translate( FavoriteWidgetMenu );
Defininition_Get_Translate( AppMusicManage );
Defininition_Get_Translate( DeleteException );
