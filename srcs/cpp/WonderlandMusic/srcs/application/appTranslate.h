#ifndef APPTRANSLATE_H_H_HEAD__FILE__
#define APPTRANSLATE_H_H_HEAD__FILE__
#include "../interface/iAppCore.h"
#include <head/head_translate_class.h>

class AppTranslate : public IAppCore {
protected:
	JsonTranslate *json = nullptr;
	DateTimeFormatTranslate *dateTimeFormat = nullptr;
	AboutWidgetTranslate *aboutWidget = nullptr;
	MainWindowTranslate *mainWindow = nullptr;
	MessageTranslate *message = nullptr;
	SystemTrayIconMenuTranslate *systemTrayIconMenu = nullptr;
	SystemTrayIconTranslate *systemTrayIcon = nullptr;
	UserMutexTranslate *userMutex = nullptr;
	AppMusicManageTranslate *appMusicManage = nullptr;
	DeleteExceptionTranslate *deleteException = nullptr;
	MusicWidgetTranslate *musicWidget = nullptr;
	SettingWidgetTranslate *settingWidget = nullptr;
	PlayerListWidgetMenuTranslate *playerListWidgetMenu = nullptr;
	FavoriteWidgetMenuTranslate *favoriteWidgetMenu = nullptr;
	bool deleteResource( ) override;

public:
	~AppTranslate( ) override;
	AppTranslate( );
	bool initBefore( ) override;
	bool initAfter( ) override;
	bool init( ) override;
	virtual JsonTranslate * getJson( ) const;
	virtual DateTimeFormatTranslate * getDateTimeFormat( ) const;
	virtual AboutWidgetTranslate * getAboutWidget( ) const;
	virtual MainWindowTranslate * getMainWindow( ) const;
	virtual MessageTranslate * getMessage( ) const;
	virtual SystemTrayIconMenuTranslate * getSystemTrayIconMenu( ) const;
	virtual SystemTrayIconTranslate * getSystemTrayIcon( ) const;
	virtual UserMutexTranslate * getUserMutex( ) const;
	virtual AppMusicManageTranslate * getAppMusicManage( ) const;
	virtual DeleteExceptionTranslate * getDeleteException( ) const;
	virtual MusicWidgetTranslate * getMusicWidget( ) const;
	virtual SettingWidgetTranslate * getSettingWidget( ) const;
	virtual PlayerListWidgetMenuTranslate * getPlayerListWidgetMenu( ) const;
	virtual FavoriteWidgetMenuTranslate * getFavoriteWidgetMenu( ) const;
};
#endif // APPTRANSLATE_H_H_HEAD__FILE__
