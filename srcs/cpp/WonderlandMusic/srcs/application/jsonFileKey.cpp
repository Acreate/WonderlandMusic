#include "jsonFileKey.h"

#include "appInstance.h"

#include "jsonKey/aboutWidgetJsonKey.h"
#include "jsonKey/appInstanceJsonKey.h"
#include "jsonKey/mainWindowJsonKey.h"
#include "jsonKey/musicInfoItemJsonKey.h"
#include "jsonKey/playerListJsonKey.h"
#include "jsonKey/playerListMenuJsonKey.h"
#include "jsonKey/playerListToolWidgetJsonKey.h"
#include "jsonKey/playerListTopWidgetJsonKey.h"
#include "jsonKey/playerWindowJsonKey.h"
#include "jsonKey/systemTrayIconJsonKey.h"

void JsonFileKey::deleteResource( ) {
	#define d_r(ptr) if(ptr) (delete ptr, ptr = nullptr)
	d_r( playerListToolWidget );
	d_r( aboutWidgetJsonFileKey );
	d_r( playerListTopWidget );
	d_r( playerWindow );
	d_r( playerList );
	d_r( mainWindow );
	d_r( musicInfoItem );
	d_r( playerListMenu );
	d_r( systemTrayIcon );
	d_r( appInstance );
}

JsonFileKey::~JsonFileKey( ) {
	deleteResource( );
}

JsonFileKey::JsonFileKey( ) {
}

bool JsonFileKey::init( ) {
	deleteResource( );

	playerListToolWidget = new PlayerListToolWidgetJsonKey;
	aboutWidgetJsonFileKey = new AboutWidgetJsonKey;
	playerListTopWidget = new PlayerListTopWidgetJsonKey;
	playerWindow = new PlayerWindowJsonKey;
	playerList = new PlayerListJsonKey;
	mainWindow = new MainWindowJsonKey;
	musicInfoItem = new MusicInfoItemJsonKey;
	playerListMenu = new PlayerListMenuJsonKey;
	systemTrayIcon = new SystemTrayIconJsonKey;
	appInstance = new AppInstanceJsonKey;
	#define if_init_result(ptr) if( ptr == nullptr || ptr->init() == false) return false
	if_init_result( playerListToolWidget );
	if_init_result( aboutWidgetJsonFileKey );
	if_init_result( playerListTopWidget );
	if_init_result( playerWindow );
	if_init_result( playerList );
	if_init_result( mainWindow );
	if_init_result( musicInfoItem );
	if_init_result( playerListMenu );
	if_init_result( systemTrayIcon );
	if_init_result( appInstance );

	return true;
}

PlayerListToolWidgetJsonKey * JsonFileKey::getPlayerListToolWidget( ) const {
	return playerListToolWidget;
}

AboutWidgetJsonKey * JsonFileKey::getAboutWidgetJsonFileKey( ) const {
	return aboutWidgetJsonFileKey;
}

PlayerListTopWidgetJsonKey * JsonFileKey::getPlayerListTopWidget( ) const {
	return playerListTopWidget;
}

PlayerWindowJsonKey * JsonFileKey::getPlayerWindow( ) const {
	return playerWindow;
}

MusicInfoItemJsonKey * JsonFileKey::getMusicInfoItem( ) const {
	return musicInfoItem;
}

PlayerListJsonKey * JsonFileKey::getPlayerList( ) const {
	return playerList;
}

MainWindowJsonKey * JsonFileKey::getMainWindow( ) const {
	return mainWindow;
}

PlayerListMenuJsonKey * JsonFileKey::getPlayerListMenu( ) const {
	return playerListMenu;
}

SystemTrayIconJsonKey * JsonFileKey::getSystemTrayIcon( ) const {
	return systemTrayIcon;
}

AppInstanceJsonKey * JsonFileKey::getAppInstance( ) const {
	return appInstance;
}
