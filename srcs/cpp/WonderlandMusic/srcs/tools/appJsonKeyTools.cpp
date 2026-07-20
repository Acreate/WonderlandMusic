#include "appJsonKeyTools.h"
#include "../application/appDataJsonKey.h"
#include "../application/appDataManage.h"
#include "../application/appInstance.h"
#include "../application/jsonKey/aboutWidgetJsonKey.h"
#include "../application/jsonKey/appDataManageJsonKey.h"
#include "../application/jsonKey/appMusicManageJsonKey.h"
#include "../application/jsonKey/appUserInterfaceManageJsonKey.h"
#include "../application/jsonKey/mainWindowJsonKey.h"
#include "../application/jsonKey/systemTrayIconJsonKey.h"

AppDataJsonKey * AppJsonKeyTools::getAppJsonKey( ) {
	auto appInstance = AppInstance::getAppInstance( );
	if( appInstance == nullptr )
		return nullptr;
	auto dataManage = appInstance->getAppDataManage( );
	if( dataManage == nullptr )
		return nullptr;
	return dataManage->getAppDataJsonKey( );
}

#define Json_Key_Type( type_name_ ) type_name_##JsonKey
#define Defininition_Get_Json_Key( type_name_ ) \
	bool AppJsonKeyTools::get##type_name_(const std::function< void(const Json_Key_Type(type_name_) & json_key) > &json_key_fun_call){\
		Json_Key_Type(type_name_) *var = nullptr; \
		auto *getPtr = getAppJsonKey( ); \
		if( getPtr ){ \
			var = getPtr->get##type_name_( );\
			if( var ) { \
				json_key_fun_call( *var ); \
				return true; \
			}\
		}\
		var = new Json_Key_Type(type_name_); \
		if( var->init( ) ) { \
			json_key_fun_call( *var ); \
			delete var; \
			return true; \
		} \
		return false;\
	}
Defininition_Get_Json_Key( AboutWidget );
Defininition_Get_Json_Key( MainWindow );
Defininition_Get_Json_Key( SystemTrayIcon );
Defininition_Get_Json_Key( AppDataManage );
Defininition_Get_Json_Key( AppUserInterfaceManage );
Defininition_Get_Json_Key( AppMusicManage );
