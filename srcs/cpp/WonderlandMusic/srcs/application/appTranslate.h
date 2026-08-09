#ifndef APPTRANSLATE_H_H_HEAD__FILE__
#define APPTRANSLATE_H_H_HEAD__FILE__
#include <interface/iAppCore.h>

class SettingWidgetTranslate;
class MusicWindowTranslate;
class DeleteExceptionTranslate;
class AppMusicManageTranslate;
class UserMutexTranslate;
class SystemTrayIconTranslate;
class SystemTrayIconMenuTranslate;
class MessageTranslate;
class MusicTitleWidgetTranslate;
class MainWindowTranslate;
class AboutWidgetTranslate;
class DateTimeFormatTranslate;
class JsonTranslate;

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
	MusicWindowTranslate *musicWindow = nullptr;
	SettingWidgetTranslate *settingWidget = nullptr;
	MusicTitleWidgetTranslate *musicTitleWidget = nullptr;
	bool deleteResource( ) override;

public:
	~AppTranslate( ) override;
	AppTranslate( );
	bool initBefore( ) override;
	bool initAfter( ) override;
	bool init( ) override;
	virtual MusicTitleWidgetTranslate * getMusicTitleWidget( ) const;
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
	virtual MusicWindowTranslate * getMusicWindow( ) const;
	virtual SettingWidgetTranslate * getSettingWidget( ) const;
};
#endif // APPTRANSLATE_H_H_HEAD__FILE__
