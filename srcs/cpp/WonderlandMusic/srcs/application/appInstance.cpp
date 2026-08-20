#include "appInstance.h"

#include <QPainter>

#include "../component/musicWindow/musicWindow.h"
#include "../component/optionWindow/optionWindow.h"

#include "../head/after_init_macro.h"
#include "../head/before_init_macro.h"
#include "../head/init_macro.h"
#include "../head/release_macro.h"
#include "../head/result_message_out.h"

#include "../item/musicInfoItem.h"

#include "../systemTrayIcon/systemTrayIcon.h"

#include "../widget/aboutWidget.h"
#include "../widget/musicFavoriteWidget.h"
#include "../widget/musicListWidget.h"
#include "../widget/musicTitleWidget.h"
#include "../widget/settingWidget.h"

#include "../window/mainWindow.h"

#include "appInstance/appDataManage.h"
#include "appInstance/appDateTimerManage.h"
#include "appInstance/appUserInterfaceManage.h"
#include "appInstance/applicationManage.h"
#include "appInstance/appUserInterfaceManage/appDrawManage.h"

AppInstance *AppInstance::instance = nullptr;

AppInstance::AppParam::~AppParam( ) {
}

AppInstance::AppParam::AppParam( int argc, char **argv, int app_flag_s ) : argc( argc ), argv( argv ), app_flag_s( app_flag_s ) {
}

int AppInstance::AppParam::getArgc( ) const {
	return argc;
}

char ** AppInstance::AppParam::getArgv( ) const {
	return argv;
}

int AppInstance::AppParam::getAppFlagS( ) const {
	return app_flag_s;
}

AppInstance * AppInstance::getAppInstance( ) {
	return instance;
}

AppInstance::AppInstance( int &argc, char **argv, int app_flag_s ) : appParam( argc, argv, app_flag_s ) {
}

bool AppInstance::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( appUserInterfaceManage );
	Delete_Resource_App_Core_Ptr( appDataManage );
	Delete_Resource_App_Core_Ptr( appDateTimerManage );
	Delete_Resource_App_Core_Ptr( applicationManage );
	instance = nullptr;
	return true;
}

AppDataManage * AppInstance::getAppDataManage( ) const {
	return appDataManage;
}

AppUserInterfaceManage * AppInstance::getAppUserInterfaceManage( ) const {
	return appUserInterfaceManage;
}

AppDateTimerManage * AppInstance::getAppDateTimerManage( ) const {
	return appDateTimerManage;
}

ApplicationManage * AppInstance::getApplicationManage( ) const {
	return applicationManage;
}

AppInstance::~AppInstance( ) {
	deleteResource( );
}

bool AppInstance::init( ) {
	Init_Resource_App_Core_Ptr( applicationManage );
	Init_Resource_App_Core_Ptr( appDateTimerManage );
	Init_Resource_App_Core_Ptr( appDataManage );
	Init_Resource_App_Core_Ptr( appUserInterfaceManage );

	return true;
}

bool AppInstance::initBefore( ) {
	deleteResource( );
	instance = this;
	applicationManage = new ApplicationManage( appParam.argc, appParam.argv, appParam.app_flag_s );
	appDateTimerManage = new AppDateTimerManage;
	appDataManage = new AppDataManage;
	appUserInterfaceManage = new AppUserInterfaceManage;
	Before_Init_Resource_App_Core_Ptr( applicationManage );
	Before_Init_Resource_App_Core_Ptr( appDateTimerManage );
	Before_Init_Resource_App_Core_Ptr( appDataManage );
	Before_Init_Resource_App_Core_Ptr( appUserInterfaceManage );
	return true;
}

bool AppInstance::initAfter( ) {
	After_Init_Resource_App_Core_Ptr( applicationManage );
	After_Init_Resource_App_Core_Ptr( appDateTimerManage );
	After_Init_Resource_App_Core_Ptr( appDataManage );
	After_Init_Resource_App_Core_Ptr( appUserInterfaceManage );

	auto musicWindow = appUserInterfaceManage->getMusicWindow( );
	auto musicFavoriteWidget = appUserInterfaceManage->getMusicFavoriteWidget( );
	if( musicWindow->setMusicFavoriteWidget( musicFavoriteWidget ) == musicFavoriteWidget )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, musicWindow, setMusicFavoriteWidget( musicFavoriteWidget ), tr( "设置音频收藏夹组件失败" ) );
	auto musicListWidget = appUserInterfaceManage->getMusicListWidget( );
	if( musicWindow->setMusicListWidget( musicListWidget ) == musicListWidget )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, musicWindow, setMusicListWidget( musicListWidget ), tr( "设置音频信息列表组件失败" ) );
	auto musicTitleWidget = appUserInterfaceManage->getMusicTitleWidget( );
	if( musicWindow->setMusicTitleWidget( musicTitleWidget ) == musicTitleWidget )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, musicWindow, setMusicTitleWidget( musicTitleWidget ), tr( "设置音频标题组件失败" ) );

	auto optionWindow = appUserInterfaceManage->getOptionWindow( );
	if( optionWindow->addOptionPanel( musicWindow ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, optionWindow, addOptionPanel( musicWindow ), tr( "添加音乐播放面板失败" ) );

	auto settingWidget = appUserInterfaceManage->getSettingWidget( );
	if( optionWindow->addOptionPanel( settingWidget ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, optionWindow, addOptionPanel( settingWidget ), tr( "添加设置面板失败" ) );

	auto aboutWidget = appUserInterfaceManage->getAboutWidget( );
	if( optionWindow->addOptionPanel( aboutWidget ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, optionWindow, addOptionPanel( aboutWidget ), tr( "添加关于面板失败" ) );

	if( optionWindow->showOptionPanel( musicWindow ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( false, optionWindow, showOptionPanel( musicWindow ), tr( "显示音乐播放面板失败" ) );

	auto mainWindow = appUserInterfaceManage->getMainWindow( );
	mainWindow->setCentralWidget( optionWindow );

	auto musicInfoItem = MusicInfoItem( appDataManage->getAppMusicManage( ) );
	musicInfoItem.setIdCode( 0 );
	musicInfoItem.setName( "123" );
	musicInfoItem.setAbsoluteFilePath( "45.mp3" );
	musicInfoItem.setSinger( "777" );
	musicInfoItem.setElapsedTime( 234 );
	musicInfoItem.setLoadedOver( true );
	QImage image = QImage( 1024, 768, QImage::Format_RGBA8888 );
	image.fill( 0 );
	QPainter painter;
	painter.begin( &image );
	appUserInterfaceManage->getAppDrawManage( )->drawItem( painter, &musicInfoItem );
	painter.end( );
	image.save( "test.png" );
	return false;
}

int AppInstance::exec( ) {
	if( appUserInterfaceManage->showMainWindow( ) == false )
		return false;
	auto systemTrayIcon = appUserInterfaceManage->getSystemTrayIcon( );
	systemTrayIcon->show( );

	int exec = applicationManage->exec( );
	if( appDataManage->writeJsonData( ) == false )
		return Result_Var_Function_Messag_Ptr_Out_Args( exec, appDataManage, writeJsonData, tr( "json 写入异常" ) );
	return exec;
}
