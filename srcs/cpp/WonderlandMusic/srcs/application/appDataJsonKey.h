#ifndef APPDATAJSONKEY_H_H_HEAD__FILE__
#define APPDATAJSONKEY_H_H_HEAD__FILE__

#include "../interface/iAppCore.h"

class FavoritemDockWidgetJsonKey;
class AppUserInterfaceManageJsonKey;
class AppDataManageJsonKey;
class MusicInfoItemWidgetJsonKey;
class SystemTrayIconJsonKey;
class PlayerListMenuJsonKey;
class PlayerWindowJsonKey;
class MainWindowJsonKey;
class PlayerListTopWidgetJsonKey;
class AboutWidgetJsonKey;
class PlayerListToolWidgetJsonKey;

class AppDataJsonKey : public IAppCore {
protected:
	PlayerListToolWidgetJsonKey *playerListToolWidget = nullptr;
	AboutWidgetJsonKey *aboutWidgetJsonFileKey = nullptr;
	PlayerListTopWidgetJsonKey *playerListTopWidget = nullptr;
	PlayerWindowJsonKey *playerWindow = nullptr;
	MusicInfoItemWidgetJsonKey *musicInfoItemWidget = nullptr;
	MainWindowJsonKey *mainWindow = nullptr;
	SystemTrayIconJsonKey *systemTrayIcon = nullptr;
	FavoritemDockWidgetJsonKey *favoritemDockWidget = nullptr;
	AppDataManageJsonKey *appDataManage = nullptr;
	AppUserInterfaceManageJsonKey *appUserInterfaceManage = nullptr;

protected:
	bool deleteResource( ) override;

public:
	~AppDataJsonKey( ) override;

	AppDataJsonKey( );

	bool init( ) override;

	bool initBefore( ) override;

	bool initAfter( ) override;

	virtual PlayerListToolWidgetJsonKey * getPlayerListToolWidget( ) const;

	virtual AboutWidgetJsonKey * getAboutWidgetJsonFileKey( ) const;

	virtual PlayerListTopWidgetJsonKey * getPlayerListTopWidget( ) const;

	virtual PlayerWindowJsonKey * getPlayerWindow( ) const;

	virtual MusicInfoItemWidgetJsonKey * getMusicInfoItemWidget( ) const;

	virtual MainWindowJsonKey * getMainWindow( ) const;

	virtual SystemTrayIconJsonKey * getSystemTrayIcon( ) const;

	virtual FavoritemDockWidgetJsonKey * getFavoritemDockWidget( ) const;

	virtual AppDataManageJsonKey * getAppDataManage( ) const;

	virtual AppUserInterfaceManageJsonKey * getAppUserInterfaceManage( ) const;
};
#endif // APPDATAJSONKEY_H_H_HEAD__FILE__
