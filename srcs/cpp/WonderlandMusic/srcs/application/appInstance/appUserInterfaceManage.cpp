#include "appUserInterfaceManage.h"
#include <QJsonObject>

#include "../../component/musicWindow/musicWindow.h"
#include "../../component/optionWindow/optionWindow.h"

#include "../../head/after_init_macro.h"
#include "../../head/before_init_macro.h"
#include "../../head/init_macro.h"
#include "../../head/release_macro.h"
#include "../../head/result_message_out.h"

#include "../../musicImpement/widget/musicFavoriteWidget.h"
#include "../../musicImpement/widget/musicListWidget.h"
#include "../../musicImpement/widget/musicTitleWidget.h"

#include "../../systemTrayIcon/systemTrayIcon.h"

#include "../../tools/pathTools.h"

#include "../../widget/aboutWidget.h"
#include "../../widget/settingWidget.h"

#include "../../window/mainWindow.h"

#include "appDataManage/jsonKey/appUserInterfaceManageJsonKey.h"

#include "appUserInterfaceManage/appDrawManage.h"
#include "appUserInterfaceManage/appMenuManage.h"

bool AppUserInterfaceManage::deleteResource( ) {
	if( systemTrayIcon )
		systemTrayIcon->hide( );
	Delete_Resource_App_Core_Ptr( appMenuManage );
	Delete_Resource_App_Core_Ptr( optionWindow );
	Delete_Resource_App_Core_Ptr( mainWindow );

	Delete_Resource_App_Core_Ptr( musicFavoriteWidget );
	Delete_Resource_App_Core_Ptr( musicListWidget );
	Delete_Resource_App_Core_Ptr( musicTitleWidget );
	Delete_Resource_App_Core_Ptr( musicWindow );

	Delete_Resource_App_Core_Ptr( settingWidget );
	Delete_Resource_App_Core_Ptr( aboutWidget );

	Delete_Resource_App_Core_Ptr( systemTrayIcon );
	Delete_Resource_App_Core_Ptr( appDrawManage );
	return true;
}

AppMenuManage * AppUserInterfaceManage::getAppMenuManage( ) const {
	return appMenuManage;
}

bool AppUserInterfaceManage::getJsonData( QJsonObject &get_json_object ) const {
	AppJsonKeyTools::getAppUserInterfaceManage( [this, &get_json_object] ( const AppUserInterfaceManageJsonKey &json_key ) {
		QJsonObject mainWindowJsonObject;
		if( mainWindow->getJsonData( mainWindowJsonObject ) == false )
			return Result_Var_Function_Messag_Ptr_Out_Args( false, mainWindow, getJsonData, tr( "获取 json 数据异常" ) );
		QJsonObject mainMenuJsonObject;
		if( appMenuManage->getJsonData( mainMenuJsonObject ) == false )
			return Result_Var_Function_Messag_Ptr_Out_Args( false, appMenuManage, getJsonData, tr( "获取 json 数据异常" ) );
		get_json_object.insert( json_key.getMainWindowJsonObject( ), mainWindowJsonObject );
		get_json_object.insert( json_key.getMainMenuJsonObject( ), mainMenuJsonObject );
		return true;
	} );

	return true;
}

bool AppUserInterfaceManage::setJsonData( const QJsonObject &set_json_object ) {
	AppJsonKeyTools::getAppUserInterfaceManage( [this, &set_json_object] ( const AppUserInterfaceManageJsonKey &json_key ) {
		auto end = set_json_object.end( );
		auto &mainWindowJsonObjectKey = json_key.getMainWindowJsonObject( );
		auto iterator = set_json_object.find( mainWindowJsonObjectKey );
		if( end == iterator )
			return Result_Var_Function_Messag_Ptr_Out_Args( false, &set_json_object, find, tr( "查找 json 数据异常: %1" ).arg( mainWindowJsonObjectKey) );
		auto mainWindowJsonObject = iterator.value( ).toObject( );

		auto &mainMenuJsonObjectKey = json_key.getMainMenuJsonObject( );
		iterator = set_json_object.find( mainMenuJsonObjectKey );
		if( end == iterator )
			return Result_Var_Function_Messag_Ptr_Out_Args( false, &set_json_object, find, tr( "查找 json 数据异常: %1" ).arg( mainMenuJsonObjectKey) );

		auto mainMenuJsonObject = iterator.value( ).toObject( );

		if( mainWindow->setJsonData( mainWindowJsonObject ) == false )
			return Result_Var_Function_Messag_Ptr_Out_Args( false, mainWindow, setJsonData, tr( "配置 json 数据异常" ) );
		if( appMenuManage->setJsonData( mainMenuJsonObject ) == false )
			return Result_Var_Function_Messag_Ptr_Out_Args( false, appMenuManage, setJsonData, tr( "配置 json 数据异常" ) );
		return true;
	} );
	return true;
}

bool AppUserInterfaceManage::init( ) {
	Init_Resource_App_Core_Ptr( appDrawManage );
	Init_Resource_App_Core_Ptr( mainWindow );
	Init_Resource_App_Core_Ptr( optionWindow );
	Init_Resource_App_Core_Ptr( musicWindow );
	Init_Resource_App_Core_Ptr( settingWidget );
	Init_Resource_App_Core_Ptr( aboutWidget );
	Init_Resource_App_Core_Ptr( musicFavoriteWidget );
	Init_Resource_App_Core_Ptr( musicListWidget );
	Init_Resource_App_Core_Ptr( musicTitleWidget );
	Init_Resource_App_Core_Ptr( systemTrayIcon );
	Init_Resource_App_Core_Ptr( appMenuManage );

	return true;
}

bool AppUserInterfaceManage::initBefore( ) {
	deleteResource( );
	appDrawManage = new AppDrawManage;
	mainWindow = new MainWindow;
	optionWindow = new OptionWindow;
	musicWindow = new MusicWindow;
	settingWidget = new SettingWidget;

	aboutWidget = new AboutWidget;
	musicFavoriteWidget = new MusicFavoriteWidget;
	musicListWidget = new MusicListWidget;
	musicTitleWidget = new MusicTitleWidget;

	systemTrayIcon = new SystemTrayIcon;
	appMenuManage = new AppMenuManage;
	Before_Init_Resource_App_Core_Ptr( appDrawManage );

	Before_Init_Resource_App_Core_Ptr( mainWindow );
	Before_Init_Resource_App_Core_Ptr( optionWindow );
	Before_Init_Resource_App_Core_Ptr( musicWindow );
	Before_Init_Resource_App_Core_Ptr( settingWidget );
	Before_Init_Resource_App_Core_Ptr( aboutWidget );
	Before_Init_Resource_App_Core_Ptr( musicFavoriteWidget );
	Before_Init_Resource_App_Core_Ptr( musicListWidget );
	Before_Init_Resource_App_Core_Ptr( musicTitleWidget );

	Before_Init_Resource_App_Core_Ptr( systemTrayIcon );
	Before_Init_Resource_App_Core_Ptr( appMenuManage );
	return true;
}

bool AppUserInterfaceManage::initAfter( ) {
	After_Init_Resource_App_Core_Ptr( appDrawManage );

	After_Init_Resource_App_Core_Ptr( mainWindow );
	After_Init_Resource_App_Core_Ptr( optionWindow );
	After_Init_Resource_App_Core_Ptr( musicWindow );
	After_Init_Resource_App_Core_Ptr( settingWidget );
	After_Init_Resource_App_Core_Ptr( aboutWidget );
	After_Init_Resource_App_Core_Ptr( musicFavoriteWidget );
	After_Init_Resource_App_Core_Ptr( musicListWidget );
	After_Init_Resource_App_Core_Ptr( musicTitleWidget );

	After_Init_Resource_App_Core_Ptr( systemTrayIcon );
	After_Init_Resource_App_Core_Ptr( appMenuManage );

	return true;
}

AppUserInterfaceManage::~AppUserInterfaceManage( ) {
	deleteResource( );
}

bool AppUserInterfaceManage::showMainWindow( ) const {
	if( mainWindow == nullptr )
		return false;
	if( musicWindow->repaintChildrenWidget( ) == false )
		return false;
	mainWindow->show( );
	mainWindow->raise( );
	mainWindow->activateWindow( );
	return true;
}

bool AppUserInterfaceManage::hideMainWindow( ) const {
	if( mainWindow == nullptr )
		return false;
	mainWindow->hide( );
	return true;
}

MainWindow * AppUserInterfaceManage::getMainWindow( ) const {
	return mainWindow;
}

SystemTrayIcon * AppUserInterfaceManage::getSystemTrayIcon( ) const {
	return systemTrayIcon;
}

AppDrawManage * AppUserInterfaceManage::getAppDrawManage( ) const {
	return appDrawManage;
}
OptionWindow * AppUserInterfaceManage::getOptionWindow( ) const {
	return optionWindow;
}
MusicWindow * AppUserInterfaceManage::getMusicWindow( ) const {
	return musicWindow;
}
SettingWidget * AppUserInterfaceManage::getSettingWidget( ) const {
	return settingWidget;
}
AboutWidget * AppUserInterfaceManage::getAboutWidget( ) const {
	return aboutWidget;
}
MusicFavoriteWidget * AppUserInterfaceManage::getMusicFavoriteWidget( ) const {
	return musicFavoriteWidget;
}
MusicListWidget * AppUserInterfaceManage::getMusicListWidget( ) const {
	return musicListWidget;
}
MusicTitleWidget * AppUserInterfaceManage::getMusicTitleWidget( ) const {
	return musicTitleWidget;
}
