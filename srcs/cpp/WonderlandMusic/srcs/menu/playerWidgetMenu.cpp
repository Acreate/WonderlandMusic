#include "playerWidgetMenu.h"

#include "../application/appInstance.h"
#include "../application/appTranslate.h"

#include "../widget/playerListWidget.h"

PlayerWidgetMenu::PlayerWidgetMenu( PlayerListWidget *player_list_widget ) : QMenu( player_list_widget ), playerListWidget( player_list_widget ) {
}

bool PlayerWidgetMenu::init( ) {
	clear( );
	auto appInstance = AppInstance::getAppInstance( );
	auto appTranslate = appInstance->getTranslate( );
	auto menu = addMenu( appTranslate->getPlayerListMenuenuPlayerMenu( ) );
	// 播放列表按钮
	auto setCurrentSelectToPlayerList = menu->addAction( appTranslate->getPlayerListMenuPlayerMenuSetCurrentPlayAction( ) );
	// 插入列表按钮
	auto insterCurrentSelectToPlayerList = menu->addAction( appTranslate->getPlayerListMenuPlayerMenuInsterCurrentPlayAction( ) );
	
	
	
	return true;
}
