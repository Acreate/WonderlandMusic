#ifndef APPDATAJSONKEY_H_H_HEAD__FILE__
#define APPDATAJSONKEY_H_H_HEAD__FILE__

#include "../interface/iAppCore.h"

class FavoriteWidgetJsonKey;
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
	FavoriteWidgetJsonKey *favoriteWidget = nullptr;

protected:
	bool deleteResource( ) override;

public:
	~AppDataJsonKey( ) override;

	AppDataJsonKey( );

	bool init( ) override;

	virtual PlayerListToolWidgetJsonKey * getPlayerListToolWidget( ) const;

	virtual AboutWidgetJsonKey * getAboutWidgetJsonFileKey( ) const;

	virtual PlayerListTopWidgetJsonKey * getPlayerListTopWidget( ) const;

	virtual PlayerWindowJsonKey * getPlayerWindow( ) const;

	virtual MusicInfoItemWidgetJsonKey * getMusicInfoItemWidget( ) const;

	virtual MainWindowJsonKey * getMainWindow( ) const;

	virtual SystemTrayIconJsonKey * getSystemTrayIcon( ) const;

	virtual FavoriteWidgetJsonKey * getFavoriteWidget( ) const;
};
#endif // APPDATAJSONKEY_H_H_HEAD__FILE__
