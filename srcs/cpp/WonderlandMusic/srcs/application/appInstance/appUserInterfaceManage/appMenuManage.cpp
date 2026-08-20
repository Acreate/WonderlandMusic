#include "appMenuManage.h"

#include <QJsonObject>

#include "../../../head/after_init_macro.h"
#include "../../../head/before_init_macro.h"
#include "../../../head/init_macro.h"
#include "../../../head/release_macro.h"
#include "../../../head/result_message_out.h"

#include "../../../menu/musicFavoriteMenu.h"
#include "../../../menu/musicListMenu.h"
#include "../../../menu/systemTrayIconMenu.h"

#include "../../../tools/widgetTools.h"

#include "../appDataManage/jsonKey/appMenuManageJsonKey.h"

AppMenuManage::AppMenuManage( ) {
}

AppMenuManage::~AppMenuManage( ) {
	deleteResource( );
}

bool AppMenuManage::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( systemTrayIconMenu );
	Delete_Resource_App_Core_Ptr( musicFavoriteMenu );
	Delete_Resource_App_Core_Ptr( musicListMenu );
	return true;
}

bool AppMenuManage::initBefore( ) {
	deleteResource( );
	systemTrayIconMenu = new SystemTrayIconMenu;
	musicFavoriteMenu = new MusicFavoriteMenu;
	musicListMenu = new MusicListMenu;
	Before_Init_Resource_App_Core_Ptr( systemTrayIconMenu );
	Before_Init_Resource_App_Core_Ptr( musicFavoriteMenu );
	Before_Init_Resource_App_Core_Ptr( musicListMenu );
	return true;
}

bool AppMenuManage::init( ) {
	Init_Resource_App_Core_Ptr( systemTrayIconMenu );
	Init_Resource_App_Core_Ptr( musicFavoriteMenu );
	Init_Resource_App_Core_Ptr( musicListMenu );

	return true;
}

bool AppMenuManage::initAfter( ) {
	After_Init_Resource_App_Core_Ptr( systemTrayIconMenu );
	After_Init_Resource_App_Core_Ptr( musicFavoriteMenu );
	After_Init_Resource_App_Core_Ptr( musicListMenu );
	return true;
}

bool AppMenuManage::popSystemTratIconMenu( const QPoint &pos ) const {
	QPoint resutPos;
	if( WidgetTools::getMenuSuggestionShowMenuPos( resutPos, pos, systemTrayIconMenu ) == false )
		return false;
	systemTrayIconMenu->exec( resutPos );
	return true;
}
bool AppMenuManage::popMusicFavoriteMenu( const QPoint &pos ) const {
	QPoint resutPos;
	auto menu = musicFavoriteMenu->toMenu( );
	if( menu == nullptr )
		return false;
	if( WidgetTools::getMenuSuggestionShowMenuPos( resutPos, pos, menu ) == false )
		return false;
	menu->exec( resutPos );
	return true;
}
bool AppMenuManage::popMusicListMenu( const QPoint &pos ) const {
	QPoint resutPos;
	auto menu = musicListMenu->toMenu( );
	if( menu == nullptr )
		return false;
	if( WidgetTools::getMenuSuggestionShowMenuPos( resutPos, pos, menu ) == false )
		return false;
	menu->exec( resutPos );
	return true;
}

SystemTrayIconMenu * AppMenuManage::getSystemTrayIconMenu( ) const {
	return systemTrayIconMenu;
}
IMusicFavoriteMenu * AppMenuManage::getMusicFavoriteMenu( ) const {
	return musicFavoriteMenu;
}
IMusicListMenu * AppMenuManage::getMusicListMenu( ) const {
	return musicListMenu;
}
bool AppMenuManage::getJsonData( QJsonObject &get_json_object ) const {
	if( AppJsonKeyTools::getAppMenuManage( [&get_json_object, this] ( const AppMenuManageJsonKey &json_key ) {
		QJsonObject musicFavoriteMenuJsonObject;
		if( musicFavoriteMenu->getJsonData( musicFavoriteMenuJsonObject ) == false )
			return false;

		QJsonObject musicListMenuJsonObject;
		if( musicListMenu->getJsonData( musicListMenuJsonObject ) == false )
			return false;

		get_json_object.insert( json_key.getMusicFavoriteMenuJsonObjectKey( ), musicFavoriteMenuJsonObject );
		get_json_object.insert( json_key.getMusicListMenuJsonObjectKey( ), musicListMenuJsonObject );

		return true;
	} ) == false )
		return false;

	return true;
}
bool AppMenuManage::setJsonData( const QJsonObject &set_json_object ) {
	if( AppJsonKeyTools::getAppMenuManage( [&set_json_object, this] ( const AppMenuManageJsonKey &json_key ) {
		auto end = set_json_object.end( );

		auto &favoriteMenuJsonObjectKey = json_key.getMusicFavoriteMenuJsonObjectKey( );
		auto find = set_json_object.find( favoriteMenuJsonObjectKey );
		if( find == end )
			return Result_Var_Function_Messag_Ptr_Out_Args( false, &set_json_object, find, tr( "查找 json 失败: %1" ).arg(favoriteMenuJsonObjectKey ) );

		QJsonObject musicFavoriteMenuJsonObject = find.value( ).toObject( );

		auto &listMenuJsonObjectKey = json_key.getMusicListMenuJsonObjectKey( );

		find = set_json_object.find( listMenuJsonObjectKey );
		if( find == end )
			return Result_Var_Function_Messag_Ptr_Out_Args( false, &set_json_object, find, tr( "查找 json 失败: %1" ).arg(listMenuJsonObjectKey ) );
		QJsonObject musicListMenuJsonObject = find.value( ).toObject( );
		if( musicFavoriteMenu->setJsonData( musicFavoriteMenuJsonObject ) == false )
			return Result_Var_Function_Messag_Ptr_Out_Args( false, musicFavoriteMenu, setJsonData, tr( "配置 json 数据错误" ) );
		if( musicListMenu->setJsonData( musicListMenuJsonObject ) == false )
			return Result_Var_Function_Messag_Ptr_Out_Args( false, musicListMenu, setJsonData, tr( "配置 json 数据错误" ) );
		return true;
	} ) == false )
		return false;

	return true;
}
