#include "appTranslate.h"
#include <QTextCodec>
#include "appDataManage.h"

#include <head/init_macro.h>
#include <head/release_macro.h>

#include <tools/instanceTools.h>

#include "translate/aboutWidgetTranslate.h"
#include "translate/appMusicManageTranslate.h"
#include "translate/dateTimeFormatTranslate.h"
#include "translate/deleteExceptionTranslate.h"
#include "translate/jsonTranslate.h"
#include "translate/mainWindowTranslate.h"
#include "translate/messageTranslate.h"
#include "translate/musicFavoriteMenuTranslate.h"
#include "translate/musicListMenuTranslate.h"
#include "translate/musicTitleWidgetTranslate.h"
#include "translate/musicWindowTranslate.h"
#include "translate/settingWidgetTranslate.h"
#include "translate/stringEditorWidgetTranslate.h"
#include "translate/systemTrayIconMenuTranslate.h"
#include "translate/systemTrayIconTranslate.h"
#include "translate/userMutexTranslate.h"

AppTranslate::AppTranslate( ) {
}

bool AppTranslate::initBefore( ) {
	deleteResource( );

	QTextCodec *utf8 = QTextCodec::codecForName( "UTF-8" );
	if( utf8 == nullptr )
		return false;
	QTextCodec::setCodecForLocale( utf8 );

	AppDataManage *appDataManage = InstanceTools::getAppDataManage( );
	auto appSettingPath = appDataManage->getAppSettingPath( );
	auto currentQMFile = appSettingPath + QObject::tr( "/translations/WonderlandMusic_zh_CN.qm" );
	appDataManage->setAppStringTranslate( currentQMFile );

	json = new JsonTranslate;
	dateTimeFormat = new DateTimeFormatTranslate;
	aboutWidget = new AboutWidgetTranslate;
	mainWindow = new MainWindowTranslate;
	message = new MessageTranslate;
	systemTrayIconMenu = new SystemTrayIconMenuTranslate;
	systemTrayIcon = new SystemTrayIconTranslate;
	userMutex = new UserMutexTranslate;
	appMusicManage = new AppMusicManageTranslate;
	deleteException = new DeleteExceptionTranslate;
	musicWindow = new MusicWindowTranslate;
	settingWidget = new SettingWidgetTranslate;
	musicTitleWidget = new MusicTitleWidgetTranslate;
	musicFavoriteMenu = new MusicFavoriteMenuTranslate;
	musicListMenu = new MusicListMenuTranslate;
	stringEditorWidget = new StringEditorWidgetTranslate;
	return true;
}

bool AppTranslate::initAfter( ) {
	return true;
}

bool AppTranslate::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( json );
	Delete_Resource_App_Core_Ptr( dateTimeFormat );
	Delete_Resource_App_Core_Ptr( aboutWidget );
	Delete_Resource_App_Core_Ptr( mainWindow );
	Delete_Resource_App_Core_Ptr( message );
	Delete_Resource_App_Core_Ptr( systemTrayIconMenu );
	Delete_Resource_App_Core_Ptr( systemTrayIcon );
	Delete_Resource_App_Core_Ptr( userMutex );
	Delete_Resource_App_Core_Ptr( appMusicManage );
	Delete_Resource_App_Core_Ptr( deleteException );
	Delete_Resource_App_Core_Ptr( musicWindow );
	Delete_Resource_App_Core_Ptr( settingWidget );
	Delete_Resource_App_Core_Ptr( musicTitleWidget );
	Delete_Resource_App_Core_Ptr( musicFavoriteMenu );
	Delete_Resource_App_Core_Ptr( musicListMenu );
	Delete_Resource_App_Core_Ptr( stringEditorWidget );
	return true;
}

AppTranslate::~AppTranslate( ) {
	deleteResource( );
}

bool AppTranslate::init( ) {
	Init_Resource_App_Core_Ptr( json );
	Init_Resource_App_Core_Ptr( dateTimeFormat );
	Init_Resource_App_Core_Ptr( aboutWidget );
	Init_Resource_App_Core_Ptr( mainWindow );
	Init_Resource_App_Core_Ptr( message );
	Init_Resource_App_Core_Ptr( systemTrayIconMenu );
	Init_Resource_App_Core_Ptr( systemTrayIcon );
	Init_Resource_App_Core_Ptr( userMutex );
	Init_Resource_App_Core_Ptr( appMusicManage );
	Init_Resource_App_Core_Ptr( deleteException );
	Init_Resource_App_Core_Ptr( musicWindow );
	Init_Resource_App_Core_Ptr( settingWidget );
	Init_Resource_App_Core_Ptr( musicTitleWidget );
	Init_Resource_App_Core_Ptr( musicFavoriteMenu );
	Init_Resource_App_Core_Ptr( musicListMenu );
	Init_Resource_App_Core_Ptr( stringEditorWidget );

	return true;
}
MusicTitleWidgetTranslate * AppTranslate::getMusicTitleWidget( ) const {
	return musicTitleWidget;
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

SystemTrayIconMenuTranslate * AppTranslate::getSystemTrayIconMenu( ) const {
	return systemTrayIconMenu;
}

SystemTrayIconTranslate * AppTranslate::getSystemTrayIcon( ) const {
	return systemTrayIcon;
}

UserMutexTranslate * AppTranslate::getUserMutex( ) const {
	return userMutex;
}

AppMusicManageTranslate * AppTranslate::getAppMusicManage( ) const {
	return appMusicManage;
}

DeleteExceptionTranslate * AppTranslate::getDeleteException( ) const {
	return deleteException;
}
MusicWindowTranslate * AppTranslate::getMusicWindow( ) const {
	return musicWindow;
}

SettingWidgetTranslate * AppTranslate::getSettingWidget( ) const {
	return settingWidget;
}
MusicFavoriteMenuTranslate * AppTranslate::getMusicFavoriteMenu( ) const {
	return musicFavoriteMenu;
}
MusicListMenuTranslate * AppTranslate::getMusicListMenu( ) const {
	return musicListMenu;
}
StringEditorWidgetTranslate * AppTranslate::getStringEditorWidget( ) const {
	return stringEditorWidget;
}
