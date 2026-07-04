#include "appTranslate.h"

#include <QTextCodec>

#include "appDataManage.h"
#include "appInstance.h"

#include "translate/aboutWidgetTranslate.h"
#include "translate/dateTimeFormatTranslate.h"
#include "translate/favoriteWidgetTranslate.h"
#include "translate/jsonTranslate.h"
#include "translate/mainWindowTranslate.h"
#include "translate/messageTranslate.h"
#include "translate/musicInfoItemTranslate.h"
#include "translate/optionDockWidgetTranslate.h"
#include "translate/playerListWidgetMenuTranlate.h"
#include "translate/playerListWidgetTranslate.h"
#include "translate/playerToolsWidgetTranslate.h"
#include "translate/playerTopWidgetTranslate.h"
#include "translate/playerWindowTranslate.h"
#include "translate/settingWidgetTranslate.h"
#include "translate/systemTrayIconMenuTranslate.h"
#include "translate/systemTrayIconTranslate.h"
#include "translate/userMutexTranslate.h"

AppTranslate::AppTranslate( ) {
}

bool AppTranslate::initBefore( ) {
	return true;
}

bool AppTranslate::initAfter( ) {
	return true;
}

bool AppTranslate::setCodecForLocale( ) {
	QTextCodec *utf8 = QTextCodec::codecForName( "UTF-8" );
	if( utf8 == nullptr )
		return false;
	QTextCodec::setCodecForLocale( utf8 );
	return true;
}

bool AppTranslate::translateString( ) {
	Init_Resource_App_Core_Ptr( settingWidget );
	Init_Resource_App_Core_Ptr( playerToolsWidget );
	Init_Resource_App_Core_Ptr( playerListWidgetMenu );
	Init_Resource_App_Core_Ptr( playerTopWidget );
	Init_Resource_App_Core_Ptr( playerWindow );
	Init_Resource_App_Core_Ptr( json );
	Init_Resource_App_Core_Ptr( dateTimeFormat );
	Init_Resource_App_Core_Ptr( aboutWidget );
	Init_Resource_App_Core_Ptr( mainWindow );
	Init_Resource_App_Core_Ptr( message );
	Init_Resource_App_Core_Ptr( playerListWidget );
	Init_Resource_App_Core_Ptr( musicInfoItem );
	Init_Resource_App_Core_Ptr( systemTrayIconMenu );
	Init_Resource_App_Core_Ptr( systemTrayIcon );
	Init_Resource_App_Core_Ptr( userMutex );
	Init_Resource_App_Core_Ptr( favoriteWidget );
	Init_Resource_App_Core_Ptr( optionDockWidget );

	return true;
}

bool AppTranslate::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( settingWidget );
	Delete_Resource_App_Core_Ptr( playerToolsWidget );
	Delete_Resource_App_Core_Ptr( playerListWidgetMenu );
	Delete_Resource_App_Core_Ptr( playerTopWidget );
	Delete_Resource_App_Core_Ptr( playerWindow );
	Delete_Resource_App_Core_Ptr( json );
	Delete_Resource_App_Core_Ptr( dateTimeFormat );
	Delete_Resource_App_Core_Ptr( aboutWidget );
	Delete_Resource_App_Core_Ptr( mainWindow );
	Delete_Resource_App_Core_Ptr( message );
	Delete_Resource_App_Core_Ptr( playerListWidget );
	Delete_Resource_App_Core_Ptr( musicInfoItem );
	Delete_Resource_App_Core_Ptr( systemTrayIconMenu );
	Delete_Resource_App_Core_Ptr( systemTrayIcon );
	Delete_Resource_App_Core_Ptr( userMutex );
	Delete_Resource_App_Core_Ptr( favoriteWidget );
	Delete_Resource_App_Core_Ptr( optionDockWidget );
	return true;
}

bool AppTranslate::loadTranslateQMFile( ) {
	auto appInstance = AppInstance::getAppInstance( );
	AppDataManage *appDataManage = appInstance->getAppDataManage( );
	auto appSettingPath = appDataManage->getAppSettingPath( );
	auto currentQMFile = appSettingPath + QObject::tr( "/translations/WonderlandMusic_zh_CN.qm" );
	appDataManage->setAppStringTranslate( currentQMFile );
	return true;
}

AppTranslate::~AppTranslate( ) {
	deleteResource( );
}

bool AppTranslate::createTranlate( ) {
	settingWidget = new SettingWidgetTranslate;
	playerToolsWidget = new PlayerToolsWidgetTranslate;
	playerListWidgetMenu = new PlayerListWidgetMenuTranlate;
	playerTopWidget = new PlayerTopWidgetTranslate;
	playerWindow = new PlayerWindowTranslate;
	json = new JsonTranslate;
	dateTimeFormat = new DateTimeFormatTranslate;
	aboutWidget = new AboutWidgetTranslate;
	mainWindow = new MainWindowTranslate;
	message = new MessageTranslate;
	playerListWidget = new PlayerListWidgetTranslate;
	musicInfoItem = new MusicInfoItemTranslate;
	systemTrayIconMenu = new SystemTrayIconMenuTranslate;
	systemTrayIcon = new SystemTrayIconTranslate;
	userMutex = new UserMutexTranslate;
	favoriteWidget = new FavoriteWidgetTranslate;
	optionDockWidget = new OptionDockWidgetTranslate;

	return true;
}

bool AppTranslate::init( ) {
	deleteResource( );

	if( setCodecForLocale( ) == false )
		return false;
	if( loadTranslateQMFile( ) == false )
		return false;
	if( createTranlate( ) == false )
		return false;
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

PlayerListWidgetMenuTranlate * AppTranslate::getPlayerListWidgetMenu( ) const {
	return playerListWidgetMenu;
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

FavoriteWidgetTranslate * AppTranslate::getFavoriteWidget( ) const {
	return favoriteWidget;
}

OptionDockWidgetTranslate * AppTranslate::getOptionDockWidget( ) const {
	return optionDockWidget;
}
