#ifndef APPTRANSLATE_H_H_HEAD__FILE__
#define APPTRANSLATE_H_H_HEAD__FILE__
#include "appCore.h"

class PlayerListWidgetMenuTranlate;
class SystemTrayIconTranslate;
class SystemTrayIconMenuTranslate;
class MusicInfoItemTranslate;
class PlayerListWidgetTranslate;
class MessageTranslate;
class MainWindowTranslate;
class AboutWidgetTranslate;
class DateTimeFormatTranslate;
class JsonTranslate;
class PlayerWindowTranslate;
class PlayerTopWidgetTranslate;
class PlayerToolsWidgetTranslate;
class SettingWidgetTranslate;
class UserMutexTranslate;
class ISelectDirWidgetTranslate;

class AppTranslate : public AppCore {
protected:
	SettingWidgetTranslate *settingWidget = nullptr;
	PlayerToolsWidgetTranslate *playerToolsWidget = nullptr;
	PlayerListWidgetMenuTranlate *playerListWidgetMenu = nullptr;
	PlayerTopWidgetTranslate *playerTopWidget = nullptr;
	PlayerWindowTranslate *playerWindow = nullptr;
	JsonTranslate *json = nullptr;
	DateTimeFormatTranslate *dateTimeFormat = nullptr;
	AboutWidgetTranslate *aboutWidget = nullptr;
	MainWindowTranslate *mainWindow = nullptr;
	MessageTranslate *message = nullptr;
	PlayerListWidgetTranslate *playerListWidget = nullptr;
	MusicInfoItemTranslate *musicInfoItem = nullptr;
	SystemTrayIconMenuTranslate *systemTrayIconMenu = nullptr;
	SystemTrayIconTranslate *systemTrayIcon = nullptr;
	UserMutexTranslate *userMutex = nullptr;

protected:
	virtual void setCodecForLocale( );

	virtual bool translateString( );

	bool deleteResource( ) override;

	virtual void loadTranslateQMFile( );

public:
	~AppTranslate( ) override;

	AppTranslate( );

	bool init( ) override;

	virtual SettingWidgetTranslate * getSettingWidget( ) const;

	virtual PlayerToolsWidgetTranslate * getPlayerToolsWidget( ) const;

	virtual PlayerListWidgetMenuTranlate * getPlayerListWidgetMenu( ) const;

	virtual PlayerTopWidgetTranslate * getPlayerTopWidget( ) const;

	virtual PlayerWindowTranslate * getPlayerWindow( ) const;

	virtual JsonTranslate * getJson( ) const;

	virtual DateTimeFormatTranslate * getDateTimeFormat( ) const;

	virtual AboutWidgetTranslate * getAboutWidget( ) const;

	virtual MainWindowTranslate * getMainWindow( ) const;

	virtual MessageTranslate * getMessage( ) const;

	virtual PlayerListWidgetTranslate * getPlayerListWidget( ) const;

	virtual MusicInfoItemTranslate * getMusicInfoItem( ) const;

	virtual SystemTrayIconMenuTranslate * getSystemTrayIconMenu( ) const;

	virtual SystemTrayIconTranslate * getSystemTrayIcon( ) const;

	virtual UserMutexTranslate * getUserMutex( ) const;
};

#endif // APPTRANSLATE_H_H_HEAD__FILE__
