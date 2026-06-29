#include "playerWidgetMenu.h"

#include "../application/appDataManage.h"
#include "../application/appEventManage.h"
#include "../application/appInstance.h"
#include "../application/appTranslate.h"
#include "../application/jsonFileKey.h"
#include "../application/musicManage.h"
#include "../application/translate/playerListMenuTranslate.h"
#include "../widget/playerListWidget.h"

PlayerWidgetMenu::PlayerWidgetMenu( PlayerListWidget *player_list_widget ) : QMenu( player_list_widget ), playerListWidget( player_list_widget ) {
}

bool PlayerWidgetMenu::initVar( ) {
	if( playerListWidget == nullptr )
		return false;
	appInstance = AppInstance::getAppInstance( );
	if( appInstance == nullptr )
		return false;
	auto appDataManage = appInstance->getAppDataManage( );
	appTranslate = appDataManage->getTranslate( );
	if( appTranslate == nullptr )
		return false;
	playerListMenuTranslate = appTranslate->getPlayerListMenu( );
	if( playerListMenuTranslate == nullptr )
		return false;
	musicDecoder = appInstance->getMusicManage( )->getMusicDecoder( );
	if( musicDecoder == nullptr )
		return false;
	jsonFileKey = appDataManage->getJsonFileKey( );
	if( jsonFileKey == nullptr )
		return false;
	playerListMenuJsonKey = jsonFileKey->getPlayerListMenu( );
	if( playerListMenuJsonKey == nullptr )
		return false;
	return true;
}

bool PlayerWidgetMenu::initSubMenu( ) {
	removeMenu = addMenu( playerListMenuTranslate->getPlayerListMenuMoveMenu( ) );
	controlMenu = addMenu( playerListMenuTranslate->getPlayerListMenuControlMenu( ) );

	loadMenu = addMenu( playerListMenuTranslate->getPlayerListMenuFileLoadMenu( ) );
	return true;
}

bool PlayerWidgetMenu::initSubMenuAcction( ) {
	setplay = controlMenu->QWidget::addAction( playerListMenuTranslate->getPlayerListMenuPlayerMenuSetCurrentPlayAction( ) );
	insterPlay = controlMenu->QWidget::addAction( playerListMenuTranslate->getPlayerListMenuPlayerMenuInsterCurrentPlayAction( ) );

	moveTop = controlMenu->QWidget::addAction( playerListMenuTranslate->getPlayerListMenuControlMenuMoveTopMusicAction( ) );
	moveBottom = controlMenu->QWidget::addAction( playerListMenuTranslate->getPlayerListMenuControlMenuMoveBottomMusicAction( ) );

	removeMusicAtList = removeMenu->QWidget::addAction( playerListMenuTranslate->getPlayerListMenuControlMenuRemoveMusicAction( ) );
	deleteMusicAtDiskFile = removeMenu->QWidget::addAction( playerListMenuTranslate->getPlayerListMenuControlMenuDeleteMusicAction( ) );

	addMultiFileMusicToCollectionAction = loadMenu->addAction( playerListMenuTranslate->getPlayerListAddMultiMusicFileToCollectionAction( ) );
	addMultiMusicDirToCollection = loadMenu->addAction( playerListMenuTranslate->getPlayerListAddMultiMusicDirToCollectionAction( ) );

	return true;
}

bool PlayerWidgetMenu::initConnectAcction( ) {
	connect( addMultiFileMusicToCollectionAction, &QAction::triggered, this, &PlayerWidgetMenu::loadDiskFile );
	connect( addMultiMusicDirToCollection, &QAction::triggered, this, &PlayerWidgetMenu::loadDiskDir );

	connect( moveTop, &QAction::triggered, this, &PlayerWidgetMenu::selectListMoveTop );
	connect( moveBottom, &QAction::triggered, this, &PlayerWidgetMenu::selectListMoveBottom );

	connect( setplay, &QAction::triggered, this, &PlayerWidgetMenu::setCurrentSelectPlay );
	connect( insterPlay, &QAction::triggered, this, &PlayerWidgetMenu::insterCurrentSelectPlay );

	connect( removeMusicAtList, &QAction::triggered, this, &PlayerWidgetMenu::removePlayListSelectInfo );
	connect( deleteMusicAtDiskFile, &QAction::triggered, this, &PlayerWidgetMenu::deletePlayListSelectFile );

	return true;
}

void PlayerWidgetMenu::loadDiskFile( ) {
	auto eventInfo = PlayerWidgetMenuEventInfo( PlayerWidgetMenuEventInfo::EventType::Load_Disk_File, this );
	Emit_PlayerWidgetMenu_Event( this, eventInfo );
}

void PlayerWidgetMenu::loadDiskDir( ) {
	auto eventInfo = PlayerWidgetMenuEventInfo( PlayerWidgetMenuEventInfo::EventType::Load_Disk_Dir, this );
	Emit_PlayerWidgetMenu_Event( this, eventInfo );
}

bool PlayerWidgetMenu::deleteResource( ) {
	clear( );
	return true;
}

bool PlayerWidgetMenu::init( ) {
	deleteResource( );
	if( initVar( ) == false )
		return false;
	if( initSubMenu( ) == false )
		return false;
	if( initSubMenuAcction( ) == false )
		return false;
	if( initConnectAcction( ) == false )
		return false;
	return true;
}

void PlayerWidgetMenu::setCurrentSelectPlay( ) {
	auto eventInfo = PlayerWidgetMenuEventInfo( PlayerWidgetMenuEventInfo::EventType::Set_Current_Select_Play, this );
	Emit_PlayerWidgetMenu_Event( this, eventInfo );
}

void PlayerWidgetMenu::insterCurrentSelectPlay( ) {
	auto eventInfo = PlayerWidgetMenuEventInfo( PlayerWidgetMenuEventInfo::EventType::Inster_Current_Select_Play, this );
	Emit_PlayerWidgetMenu_Event( this, eventInfo );
}

void PlayerWidgetMenu::removePlayListSelectInfo( ) {
	auto eventInfo = PlayerWidgetMenuEventInfo( PlayerWidgetMenuEventInfo::EventType::Remove_Play_List_Select_Info, this );
	Emit_PlayerWidgetMenu_Event( this, eventInfo );
}

void PlayerWidgetMenu::deletePlayListSelectFile( ) {
	auto eventInfo = PlayerWidgetMenuEventInfo( PlayerWidgetMenuEventInfo::EventType::Delete_Play_List_Select_File, this );
	Emit_PlayerWidgetMenu_Event( this, eventInfo );
}

void PlayerWidgetMenu::selectListMoveTop( ) {
	auto eventInfo = PlayerWidgetMenuEventInfo( PlayerWidgetMenuEventInfo::EventType::Select_List_Move_Top, this );
	Emit_PlayerWidgetMenu_Event( this, eventInfo );
}

void PlayerWidgetMenu::selectListMoveBottom( ) {
	auto eventInfo = PlayerWidgetMenuEventInfo( PlayerWidgetMenuEventInfo::EventType::Select_List_Move_Bottom, this );
	Emit_PlayerWidgetMenu_Event( this, eventInfo );
}
