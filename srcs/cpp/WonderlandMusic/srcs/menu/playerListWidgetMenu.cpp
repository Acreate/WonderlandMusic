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

bool PlayerListWidgetMenu::deleteResource( ) {
	clear( );
	return true;
}

bool PlayerListWidgetMenu::init( ) {
	return true;
}

bool PlayerListWidgetMenu::initBefore( ) {
	deleteResource( );
	auto appInstance = AppInstance::getAppInstance( );
	if( appInstance == nullptr )
		return false;
	auto appDataManage = appInstance->getAppDataManage( );
	auto appTranslate = appDataManage->getTranslate( );
	if( appTranslate == nullptr )
		return false;
	auto playerListWidgetMenuTranlate = appTranslate->getPlayerListWidgetMenu( );
	if( playerListWidgetMenuTranlate == nullptr )
		return false;
	auto musicDecoder = appInstance->getAppDataManage( )->getAppMusicManage( )->getAppMusicDecoder( );
	if( musicDecoder == nullptr )
		return false;
	auto jsonFileKey = appDataManage->getAppDataJsonKey( );
	if( jsonFileKey == nullptr )
		return false;

	removeMenu = addMenu( playerListWidgetMenuTranlate->getPlayerListMenuMoveMenu( ) );
	controlMenu = addMenu( playerListWidgetMenuTranlate->getPlayerListMenuControlMenu( ) );

	loadMenu = addMenu( playerListWidgetMenuTranlate->getPlayerListMenuFileLoadMenu( ) );

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

bool PlayerListWidgetMenu::initAfter( ) {
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
