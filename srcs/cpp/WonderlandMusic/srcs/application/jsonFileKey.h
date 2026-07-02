#ifndef JSONFILEKEY_H_H_HEAD__FILE__
#define JSONFILEKEY_H_H_HEAD__FILE__
#include "appCore.h"

class MusicInfoItemWidgetJsonKey;
class SystemTrayIconJsonKey;
class PlayerListMenuJsonKey;
class PlayerWindowJsonKey;
class MainWindowJsonKey;
class PlayerListTopWidgetJsonKey;
class AboutWidgetJsonKey;
class PlayerListToolWidgetJsonKey;

class JsonFileKey : public AppCore {
protected:
	PlayerListToolWidgetJsonKey *playerListToolWidget = nullptr;
	AboutWidgetJsonKey *aboutWidgetJsonFileKey = nullptr;
	PlayerListTopWidgetJsonKey *playerListTopWidget = nullptr;
	PlayerWindowJsonKey *playerWindow = nullptr;
	MusicInfoItemWidgetJsonKey *musicInfoItemWidget = nullptr;
	MainWindowJsonKey *mainWindow = nullptr;
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

	virtual MusicInfoItemWidgetJsonKey * getMusicInfoItemWidget( ) const;

	virtual MainWindowJsonKey * getMainWindow( ) const;

	virtual SystemTrayIconJsonKey * getSystemTrayIcon( ) const;
};

#endif // JSONFILEKEY_H_H_HEAD__FILE__
