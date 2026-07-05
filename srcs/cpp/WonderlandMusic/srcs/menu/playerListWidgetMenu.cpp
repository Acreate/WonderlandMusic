#include "playerListWidgetMenu.h"

#include "../application/appDataManage.h"
#include "../application/appInstance.h"
#include "../application/appMusicManage.h"
#include "../application/appTranslate.h"
#include "../application/translate/playerListWidgetMenuTranlate.h"

PlayerListWidgetMenu::PlayerListWidgetMenu( ) : QMenu( ) {
}

PlayerListWidgetMenu::~PlayerListWidgetMenu( ) {
	deleteResource( );
}

bool PlayerListWidgetMenu::initVar( ) {
	appInstance = AppInstance::getAppInstance( );
	if( appInstance == nullptr )
		return false;
	auto appDataManage = appInstance->getAppDataManage( );
	appTranslate = appDataManage->getTranslate( );
	if( appTranslate == nullptr )
		return false;
	playerListWidgetMenuTranlate = appTranslate->getPlayerListWidgetMenu( );
	if( playerListWidgetMenuTranlate == nullptr )
		return false;
	musicDecoder = appInstance->getAppDataManage( )->getAppMusicManage( )->getAppMusicDecoder( );
	if( musicDecoder == nullptr )
		return false;
	jsonFileKey = appDataManage->getAppDataJsonKey( );
	if( jsonFileKey == nullptr )
		return false;
	return true;
}

bool PlayerListWidgetMenu::initSubMenu( ) {
	removeMenu = addMenu( playerListWidgetMenuTranlate->getPlayerListMenuMoveMenu( ) );
	controlMenu = addMenu( playerListWidgetMenuTranlate->getPlayerListMenuControlMenu( ) );

	loadMenu = addMenu( playerListWidgetMenuTranlate->getPlayerListMenuFileLoadMenu( ) );
	return true;
}

bool PlayerListWidgetMenu::initSubMenuAcction( ) {
	setplay = controlMenu->QWidget::addAction( playerListWidgetMenuTranlate->getPlayerListMenuPlayerMenuSetCurrentPlayAction( ) );
	insterPlay = controlMenu->QWidget::addAction( playerListWidgetMenuTranlate->getPlayerListMenuPlayerMenuInsterCurrentPlayAction( ) );

	moveTop = controlMenu->QWidget::addAction( playerListWidgetMenuTranlate->getPlayerListMenuControlMenuMoveTopMusicAction( ) );
	moveBottom = controlMenu->QWidget::addAction( playerListWidgetMenuTranlate->getPlayerListMenuControlMenuMoveBottomMusicAction( ) );

	removeMusicAtList = removeMenu->QWidget::addAction( playerListWidgetMenuTranlate->getPlayerListMenuControlMenuRemoveMusicAction( ) );
	deleteMusicAtDiskFile = removeMenu->QWidget::addAction( playerListWidgetMenuTranlate->getPlayerListMenuControlMenuDeleteMusicAction( ) );

	addMultiFileMusicToCollectionAction = loadMenu->addAction( playerListWidgetMenuTranlate->getPlayerListAddMultiMusicFileToCollectionAction( ) );
	addMultiMusicDirToCollection = loadMenu->addAction( playerListWidgetMenuTranlate->getPlayerListAddMultiMusicDirToCollectionAction( ) );

	return true;
}

bool PlayerListWidgetMenu::initConnectAcction( ) {
	connect( addMultiFileMusicToCollectionAction, &QAction::triggered, this, &PlayerListWidgetMenu::loadDiskFile );
	connect( addMultiMusicDirToCollection, &QAction::triggered, this, &PlayerListWidgetMenu::loadDiskDir );

	connect( moveTop, &QAction::triggered, this, &PlayerListWidgetMenu::selectListMoveTop );
	connect( moveBottom, &QAction::triggered, this, &PlayerListWidgetMenu::selectListMoveBottom );

	connect( setplay, &QAction::triggered, this, &PlayerListWidgetMenu::setCurrentSelectPlay );
	connect( insterPlay, &QAction::triggered, this, &PlayerListWidgetMenu::insterCurrentSelectPlay );

	connect( removeMusicAtList, &QAction::triggered, this, &PlayerListWidgetMenu::removePlayListSelectInfo );
	connect( deleteMusicAtDiskFile, &QAction::triggered, this, &PlayerListWidgetMenu::deletePlayListSelectFile );

	return true;
}

bool PlayerListWidgetMenu::deleteResource( ) {
	clear( );
	return true;
}

bool PlayerListWidgetMenu::init( ) {
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

bool PlayerListWidgetMenu::initBefore( ) {
	return false;
}

bool PlayerListWidgetMenu::initAfter( ) {
	return false;
}
