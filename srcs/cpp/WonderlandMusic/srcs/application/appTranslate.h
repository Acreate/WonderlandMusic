#ifndef APPTRANSLATE_H_H_HEAD__FILE__
#define APPTRANSLATE_H_H_HEAD__FILE__

#include "../interface/iAppCore.h"

class PlayerListWidgetMenuTranslate;
class DeleteExceptionTranslate;
class FavoriteWidgetMenuTranslate;
class OptionDockWidgetTranslate;
class FavoriteWidgetTranslate;
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
class AppMusicManageTranslate;

class AppTranslate : public IAppCore {
protected:
	SettingWidgetTranslate *settingWidget = nullptr;
	PlayerToolsWidgetTranslate *playerToolsWidget = nullptr;
	PlayerListWidgetMenuTranslate *playerListWidgetMenu = nullptr;
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
	FavoriteWidgetTranslate *favoriteWidget = nullptr;
	OptionDockWidgetTranslate *optionDockWidget = nullptr;
	FavoriteWidgetMenuTranslate *favoriteWidgetMenu = nullptr;
	AppMusicManageTranslate *appMusicManage = nullptr;
	DeleteExceptionTranslate *deleteException = nullptr;

protected:
	bool deleteResource( ) override;

public:
	~AppTranslate( ) override;

	AppTranslate( );

	bool initBefore( ) override;

	bool initAfter( ) override;

	bool init( ) override;

	virtual PlayerListWidgetMenuTranslate * getPlayerListWidgetMenu( ) const;

	virtual SettingWidgetTranslate * getSettingWidget( ) const;

	virtual PlayerToolsWidgetTranslate * getPlayerToolsWidget( ) const;

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

	virtual FavoriteWidgetTranslate * getFavoriteWidget( ) const;

	virtual OptionDockWidgetTranslate * getOptionDockWidget( ) const;

	virtual FavoriteWidgetMenuTranslate * getFavoriteWidgetMenu( ) const;

	virtual AppMusicManageTranslate * getAppMusicManage( ) const;

	virtual DeleteExceptionTranslate * getDeleteException( ) const;
};

#endif // APPTRANSLATE_H_H_HEAD__FILE__
