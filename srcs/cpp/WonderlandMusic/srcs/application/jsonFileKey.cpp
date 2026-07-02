#include "jsonFileKey.h"

#include "appInstance.h"

#include "../tools/templateArgs.h"

#include "jsonKey/aboutWidgetJsonKey.h"
#include "jsonKey/mainWindowJsonKey.h"
#include "jsonKey/musicInfoItemWidgetJsonKey.h"
#include "jsonKey/playerListToolWidgetJsonKey.h"
#include "jsonKey/playerListTopWidgetJsonKey.h"
#include "jsonKey/playerWindowJsonKey.h"
#include "jsonKey/systemTrayIconJsonKey.h"

bool JsonFileKey::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( playerListToolWidget );
	Delete_Resource_App_Core_Ptr( aboutWidgetJsonFileKey );
	Delete_Resource_App_Core_Ptr( playerListTopWidget );
	Delete_Resource_App_Core_Ptr( playerWindow );
	Delete_Resource_App_Core_Ptr( mainWindow );
	Delete_Resource_App_Core_Ptr( musicInfoItemWidget );
	Delete_Resource_App_Core_Ptr( systemTrayIcon );

	return true;
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
	mainWindow = new MainWindowJsonKey;
	musicInfoItemWidget = new MusicInfoItemWidgetJsonKey;
	systemTrayIcon = new SystemTrayIconJsonKey;

	Init_Resource_App_Core_Ptr( playerListToolWidget );
	Init_Resource_App_Core_Ptr( aboutWidgetJsonFileKey );
	Init_Resource_App_Core_Ptr( playerListTopWidget );
	Init_Resource_App_Core_Ptr( playerWindow );
	Init_Resource_App_Core_Ptr( mainWindow );
	Init_Resource_App_Core_Ptr( musicInfoItemWidget );
	Init_Resource_App_Core_Ptr( systemTrayIcon );

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

MusicInfoItemWidgetJsonKey * JsonFileKey::getMusicInfoItemWidget( ) const {
	return musicInfoItemWidget;
}

MainWindowJsonKey * JsonFileKey::getMainWindow( ) const {
	return mainWindow;
}

SystemTrayIconJsonKey * JsonFileKey::getSystemTrayIcon( ) const {
	return systemTrayIcon;
}
