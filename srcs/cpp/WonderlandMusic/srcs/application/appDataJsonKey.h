#ifndef APPDATAJSONKEY_H_H_HEAD__FILE__
#define APPDATAJSONKEY_H_H_HEAD__FILE__

#include "../interface/iAppCore.h"

class FavorItemWidgetJsonKey;
class MusicItemJsonKey;
class AppMusicManageJsonKey;
class FavoriteWidgetJsonKey;
class FavoriteSrollAreaJsonKey;
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
	AppDataManageJsonKey *appDataManage = nullptr;
	AppUserInterfaceManageJsonKey *appUserInterfaceManage = nullptr;
	FavoriteSrollAreaJsonKey *favoriteSrollArea = nullptr;
	FavoritemDockWidgetJsonKey *favoritemDockWidget = nullptr;
	FavoriteWidgetJsonKey *favoriteWidget = nullptr;
	AppMusicManageJsonKey *appMusicManage = nullptr;
	FavorItemWidgetJsonKey *favorItemWidget = nullptr;
	MusicItemJsonKey *musicItem = nullptr;

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

	virtual AppDataManageJsonKey * getAppDataManage( ) const;

	virtual AppUserInterfaceManageJsonKey * getAppUserInterfaceManage( ) const;

	virtual FavoriteSrollAreaJsonKey * getFavoriteSrollArea( ) const;

	virtual FavoritemDockWidgetJsonKey * getFavoritemDockWidget( ) const;

	virtual FavoriteWidgetJsonKey * getFavoriteWidget( ) const;

	virtual AppMusicManageJsonKey * getAppMusicManage( ) const;

	virtual FavorItemWidgetJsonKey * getFavorItemWidget( ) const;

	virtual MusicItemJsonKey * getMusicItem( ) const;
};
#endif // APPDATAJSONKEY_H_H_HEAD__FILE__
