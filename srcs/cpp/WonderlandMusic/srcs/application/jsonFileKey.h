#ifndef JSONFILEKEY_H_H_HEAD__FILE__
#define JSONFILEKEY_H_H_HEAD__FILE__
#include "appCore.h"

class SystemTrayIconJsonKey;
class PlayerListMenuJsonKey;
class PlayerWindowJsonKey;
class PlayerListJsonKey;
class MainWindowJsonKey;
class MusicInfoItemJsonKey;
class PlayerListTopWidgetJsonKey;
class AboutWidgetJsonKey;
class PlayerListToolWidgetJsonKey;

class JsonFileKey : public AppCore {
protected:
	PlayerListToolWidgetJsonKey *playerListToolWidget = nullptr;
	AboutWidgetJsonKey *aboutWidgetJsonFileKey = nullptr;
	PlayerListTopWidgetJsonKey *playerListTopWidget = nullptr;
	PlayerWindowJsonKey *playerWindow = nullptr;
	MusicInfoItemJsonKey *musicInfoItem = nullptr;
	PlayerListJsonKey *playerList = nullptr;
	MainWindowJsonKey *mainWindow = nullptr;
	PlayerListMenuJsonKey *playerListMenu = nullptr;
	SystemTrayIconJsonKey *systemTrayIcon = nullptr;

protected:
	bool deleteResource( ) override;

public:
	~JsonFileKey( ) override;

	JsonFileKey( );

	bool init( ) override;

	virtual PlayerListToolWidgetJsonKey * getPlayerListToolWidget( ) const;

	virtual AboutWidgetJsonKey * getAboutWidgetJsonFileKey( ) const;

	virtual PlayerListTopWidgetJsonKey * getPlayerListTopWidget( ) const;

	virtual PlayerWindowJsonKey * getPlayerWindow( ) const;

	virtual MusicInfoItemJsonKey * getMusicInfoItem( ) const;

	virtual PlayerListJsonKey * getPlayerList( ) const;

	virtual MainWindowJsonKey * getMainWindow( ) const;

	virtual PlayerListMenuJsonKey * getPlayerListMenu( ) const;

	virtual SystemTrayIconJsonKey * getSystemTrayIcon( ) const;
};

#endif // JSONFILEKEY_H_H_HEAD__FILE__
