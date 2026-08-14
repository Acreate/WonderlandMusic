#ifndef APPDATAJSONKEY_H_H_HEAD__FILE__
#define APPDATAJSONKEY_H_H_HEAD__FILE__
#include "../interface/iAppCore.h"

class AppMusicManageJsonKey;
class AppUserInterfaceManageJsonKey;
class AppDataManageJsonKey;
class SystemTrayIconJsonKey;
class MainWindowJsonKey;
class AboutWidgetJsonKey;
class MusicFavoriteMenuJsonKey;
class MusicListMenuJsonKey;
class MusicWindowJsonKey;

class AppDataJsonKey : public IAppCore {
protected:
	AboutWidgetJsonKey *aboutWidget = nullptr;
	MainWindowJsonKey *mainWindow = nullptr;
	SystemTrayIconJsonKey *systemTrayIcon = nullptr;
	AppDataManageJsonKey *appDataManage = nullptr;
	AppUserInterfaceManageJsonKey *appUserInterfaceManage = nullptr;
	AppMusicManageJsonKey *appMusicManage = nullptr;
	MusicWindowJsonKey *musicWindow = nullptr;
	MusicListMenuJsonKey *musicListMenu = nullptr;
	MusicFavoriteMenuJsonKey *musicFavoriteMenu = nullptr;

protected:
	bool deleteResource( ) override;

public:
	~AppDataJsonKey( ) override;
	AppDataJsonKey( );
	bool init( ) override;
	bool initBefore( ) override;
	bool initAfter( ) override;
	virtual MusicWindowJsonKey * getMusicWindow( ) const;
	virtual AboutWidgetJsonKey * getAboutWidget( ) const;
	virtual MainWindowJsonKey * getMainWindow( ) const;
	virtual SystemTrayIconJsonKey * getSystemTrayIcon( ) const;
	virtual AppDataManageJsonKey * getAppDataManage( ) const;
	virtual AppUserInterfaceManageJsonKey * getAppUserInterfaceManage( ) const;
	virtual AppMusicManageJsonKey * getAppMusicManage( ) const;
	virtual MusicListMenuJsonKey * getMusicListMenu( ) const;
	virtual MusicFavoriteMenuJsonKey * getMusicFavoriteMenu( ) const;
};
#endif // APPDATAJSONKEY_H_H_HEAD__FILE__
