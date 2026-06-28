#include "jsonFileKey.h"

#include "appInstance.h"

#include "../tools/templateArgs.h"

#include "jsonKey/aboutWidgetJsonKey.h"
#include "jsonKey/mainWindowJsonKey.h"
#include "jsonKey/musicInfoItemJsonKey.h"
#include "jsonKey/playerListJsonKey.h"
#include "jsonKey/playerListMenuJsonKey.h"
#include "jsonKey/playerListToolWidgetJsonKey.h"
#include "jsonKey/playerListTopWidgetJsonKey.h"
#include "jsonKey/playerWindowJsonKey.h"
#include "jsonKey/systemTrayIconJsonKey.h"

bool JsonFileKey::deleteResource( ) {
	if( TemplateArgs::delete_ptr( playerListToolWidget ) == false )
		return false;
	if( TemplateArgs::delete_ptr( aboutWidgetJsonFileKey ) == false )
		return false;
	if( TemplateArgs::delete_ptr( playerListTopWidget ) == false )
		return false;
	if( TemplateArgs::delete_ptr( playerWindow ) == false )
		return false;
	if( TemplateArgs::delete_ptr( playerList ) == false )
		return false;
	if( TemplateArgs::delete_ptr( mainWindow ) == false )
		return false;
	if( TemplateArgs::delete_ptr( musicInfoItem ) == false )
		return false;
	if( TemplateArgs::delete_ptr( playerListMenu ) == false )
		return false;
	if( TemplateArgs::delete_ptr( systemTrayIcon ) == false )
		return false;
	return true;
}

JsonFileKey::~JsonFileKey( ) {
	deleteResource( );
}

JsonFileKey::JsonFileKey( ) {
}

bool JsonFileKey::init( ) {
	deleteResource( );
	if( TemplateArgs::make_ptr( playerListToolWidget ) == nullptr )
		return false;
	if( TemplateArgs::make_ptr( aboutWidgetJsonFileKey ) == nullptr )
		return false;
	if( TemplateArgs::make_ptr( playerListTopWidget ) == nullptr )
		return false;
	if( TemplateArgs::make_ptr( playerWindow ) == nullptr )
		return false;
	if( TemplateArgs::make_ptr( playerList ) == nullptr )
		return false;
	if( TemplateArgs::make_ptr( mainWindow ) == nullptr )
		return false;
	if( TemplateArgs::make_ptr( musicInfoItem ) == nullptr )
		return false;
	if( TemplateArgs::make_ptr( playerListMenu ) == nullptr )
		return false;
	if( TemplateArgs::make_ptr( systemTrayIcon ) == nullptr )
		return false;

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
