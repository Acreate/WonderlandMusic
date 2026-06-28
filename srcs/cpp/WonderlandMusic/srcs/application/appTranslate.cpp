#include "appTranslate.h"

#include <QTextCodec>

#include "appDataManage.h"
#include "appInstance.h"

#include "../tools/templateArgs.h"

#include "translate/aboutWidgetTranslate.h"
#include "translate/dateTimeFormatTranslate.h"
#include "translate/jsonTranslate.h"
#include "translate/mainWindowTranslate.h"
#include "translate/messageTranslate.h"
#include "translate/musicInfoItemTranslate.h"
#include "translate/playerListMenuTranslate.h"
#include "translate/playerListWidgetTranslate.h"
#include "translate/playerToolsWidgetTranslate.h"
#include "translate/playerTopWidgetTranslate.h"
#include "translate/playerWidgetTranslate.h"
#include "translate/playerWindowTranslate.h"
#include "translate/settingWidgetTranslate.h"
#include "translate/systemTrayIconMenuTranslate.h"
#include "translate/systemTrayIconTranslate.h"
#include "translate/userMutexTranslate.h"

AppTranslate::AppTranslate( ) {
}

void AppTranslate::setCodecForLocale( ) {
	QTextCodec *utf8 = QTextCodec::codecForName( "UTF-8" );
	QTextCodec::setCodecForLocale( utf8 );
}

bool AppTranslate::translateString( ) {
	#define if_init_result( obj ) if(obj->init() == false) return false;
	if_init_result( settingWidget );
	if_init_result( playerToolsWidget );
	if_init_result( playerListMenu );
	if_init_result( playerTopWidget );
	if_init_result( playerWindow );
	if_init_result( json );
	if_init_result( dateTimeFormat );
	if_init_result( aboutWidget );
	if_init_result( playerWidget );
	if_init_result( mainWindow );
	if_init_result( message );
	if_init_result( playerListWidget );
	if_init_result( musicInfoItem );
	if_init_result( systemTrayIconMenu );
	if_init_result( systemTrayIcon );
	if_init_result( userMutex );

	return true;
}

bool AppTranslate::deleteResource( ) {
	if( TemplateArgs::delete_ptr( settingWidget ) == false )
		return false;
	if( TemplateArgs::delete_ptr( playerToolsWidget ) == false )
		return false;
	if( TemplateArgs::delete_ptr( playerListMenu ) == false )
		return false;
	if( TemplateArgs::delete_ptr( playerTopWidget ) == false )
		return false;
	if( TemplateArgs::delete_ptr( playerWindow ) == false )
		return false;
	if( TemplateArgs::delete_ptr( json ) == false )
		return false;
	if( TemplateArgs::delete_ptr( dateTimeFormat ) == false )
		return false;
	if( TemplateArgs::delete_ptr( aboutWidget ) == false )
		return false;
	if( TemplateArgs::delete_ptr( playerWidget ) == false )
		return false;
	if( TemplateArgs::delete_ptr( mainWindow ) == false )
		return false;
	if( TemplateArgs::delete_ptr( message ) == false )
		return false;
	if( TemplateArgs::delete_ptr( playerListWidget ) == false )
		return false;
	if( TemplateArgs::delete_ptr( musicInfoItem ) == false )
		return false;
	if( TemplateArgs::delete_ptr( systemTrayIconMenu ) == false )
		return false;
	if( TemplateArgs::delete_ptr( systemTrayIcon ) == false )
		return false;
	if( TemplateArgs::delete_ptr( userMutex ) == false )
		return false;
	return true;
}

void AppTranslate::loadTranslateQMFile( ) {
	auto appInstance = AppInstance::getAppInstance( );
	AppDataManage *appDataManage = appInstance->getAppDataManage( );
	auto appSettingPath = appDataManage->getAppSettingPath( );
	auto currentQMFile = appSettingPath + QObject::tr( "/translations/WonderlandMusic_zh_CN.qm" );
	appDataManage->setAppStringTranslate( currentQMFile );
}

AppTranslate::~AppTranslate( ) {
	deleteResource( );
}

bool AppTranslate::init( ) {
	deleteResource( );

	setCodecForLocale( );

	loadTranslateQMFile( );

	settingWidget = new SettingWidgetTranslate;
	playerToolsWidget = new PlayerToolsWidgetTranslate;
	playerListMenu = new PlayerListMenuTranslate;
	playerTopWidget = new PlayerTopWidgetTranslate;
	playerWindow = new PlayerWindowTranslate;
	json = new JsonTranslate;
	dateTimeFormat = new DateTimeFormatTranslate;
	aboutWidget = new AboutWidgetTranslate;
	playerWidget = new PlayerWidgetTranslate;
	mainWindow = new MainWindowTranslate;
	message = new MessageTranslate;
	playerListWidget = new PlayerListWidgetTranslate;
	musicInfoItem = new MusicInfoItemTranslate;
	systemTrayIconMenu = new SystemTrayIconMenuTranslate;
	systemTrayIcon = new SystemTrayIconTranslate;
	userMutex = new UserMutexTranslate;

	if( translateString( ) == false )
		return false;
	return true;
}

SettingWidgetTranslate * AppTranslate::getSettingWidget( ) const {
	return settingWidget;
}

PlayerToolsWidgetTranslate * AppTranslate::getPlayerToolsWidget( ) const {
	return playerToolsWidget;
}

PlayerListMenuTranslate * AppTranslate::getPlayerListMenu( ) const {
	return playerListMenu;
}

PlayerTopWidgetTranslate * AppTranslate::getPlayerTopWidget( ) const {
	return playerTopWidget;
}

PlayerWindowTranslate * AppTranslate::getPlayerWindow( ) const {
	return playerWindow;
}

JsonTranslate * AppTranslate::getJson( ) const {
	return json;
}

DateTimeFormatTranslate * AppTranslate::getDateTimeFormat( ) const {
	return dateTimeFormat;
}

AboutWidgetTranslate * AppTranslate::getAboutWidget( ) const {
	return aboutWidget;
}

PlayerWidgetTranslate * AppTranslate::getPlayerWidget( ) const {
	return playerWidget;
}

MainWindowTranslate * AppTranslate::getMainWindow( ) const {
	return mainWindow;
}

MessageTranslate * AppTranslate::getMessage( ) const {
	return message;
}

PlayerListWidgetTranslate * AppTranslate::getPlayerListWidget( ) const {
	return playerListWidget;
}

MusicInfoItemTranslate * AppTranslate::getMusicInfoItem( ) const {
	return musicInfoItem;
}

SystemTrayIconMenuTranslate * AppTranslate::getSystemTrayIconMenu( ) const {
	return systemTrayIconMenu;
}

SystemTrayIconTranslate * AppTranslate::getSystemTrayIcon( ) const {
	return systemTrayIcon;
}

UserMutexTranslate * AppTranslate::getUserMutex( ) const {
	return userMutex;
}
