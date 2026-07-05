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

	removeMenu = addMenu( playerListWidgetMenuTranlate->getRemoveMenu( ) );
	controlMenu = addMenu( playerListWidgetMenuTranlate->getControlMenu( ) );

	loadMenu = addMenu( playerListWidgetMenuTranlate->getFilePathLoadMenu( ) );

	insterPlayBefore = controlMenu->QWidget::addAction( playerListWidgetMenuTranlate->getAggregateToPlayerBefore( ) );
	insterPlayAfter = controlMenu->QWidget::addAction( playerListWidgetMenuTranlate->getAggregateToPlayerAfter( ) );

	moveTop = controlMenu->QWidget::addAction( playerListWidgetMenuTranlate->getMoveTopAction( ) );
	moveBottom = controlMenu->QWidget::addAction( playerListWidgetMenuTranlate->getMoveBottomAction( ) );

	aggregateToSelectFirst = controlMenu->QWidget::addAction( playerListWidgetMenuTranlate->getAggregateToSelectFirst( ) );
	aggregateToSelectLast = controlMenu->QWidget::addAction( playerListWidgetMenuTranlate->getAggregateToSelectLast( ) );

	removeMusicAtList = removeMenu->QWidget::addAction( playerListWidgetMenuTranlate->getRemoveMusciItemAction( ) );
	deleteMusicAtDiskFile = removeMenu->QWidget::addAction( playerListWidgetMenuTranlate->getDeleteMusicFileAction( ) );

	opendSelectFileDialogAction = loadMenu->addAction( playerListWidgetMenuTranlate->getLoadFileAction( ) );
	oopenSelectDirDialogAction = loadMenu->addAction( playerListWidgetMenuTranlate->getLoadDirAction( ) );

	return true;
}

bool PlayerListWidgetMenu::initAfter( ) {
	connect( aggregateToSelectFirst, &QAction::triggered, []( ) {
		auto manage = AppInstance::getAppInstance( )->getAppDataManage( )->getAppMusicManage( );
		manage->selectMusicItemAggregateToSelectFirst( );
	} );
	connect( aggregateToSelectLast, &QAction::triggered, []( ) {
		auto manage = AppInstance::getAppInstance( )->getAppDataManage( )->getAppMusicManage( );
		manage->selectMusicItemAggregateToSelectLast( );
	} );
	connect( opendSelectFileDialogAction, &QAction::triggered, []( ) {
		auto manage = AppInstance::getAppInstance( )->getAppDataManage( )->getAppMusicManage( );
		manage->openSelectMusicFileDialog( );
	} );
	connect( oopenSelectDirDialogAction, &QAction::triggered, []( ) {
		auto manage = AppInstance::getAppInstance( )->getAppDataManage( )->getAppMusicManage( );
		manage->openSelectMusicDirDialog( );
	} );

	connect( moveTop, &QAction::triggered, []( ) {
		auto manage = AppInstance::getAppInstance( )->getAppDataManage( )->getAppMusicManage( );
		manage->selectMusicItemMoveToTop( );
	} );
	connect( moveBottom, &QAction::triggered, []( ) {
		auto manage = AppInstance::getAppInstance( )->getAppDataManage( )->getAppMusicManage( );
		manage->selectMusicItemMoveToBottom( );
	} );

	connect( insterPlayBefore, &QAction::triggered, []( ) {
		auto manage = AppInstance::getAppInstance( )->getAppDataManage( )->getAppMusicManage( );
		manage->selectMusicItemAggregateToPlayItemBefore( );
	} );
	connect( insterPlayAfter, &QAction::triggered, []( ) {
		auto manage = AppInstance::getAppInstance( )->getAppDataManage( )->getAppMusicManage( );
		manage->selectMusicItemAggregateToPlayItemAfter( );
	} );

	connect( removeMusicAtList, &QAction::triggered, [ ]( ) {
		auto manage = AppInstance::getAppInstance( )->getAppDataManage( )->getAppMusicManage( );
		manage->removeSelectMusicItem( );
	} );
	connect( deleteMusicAtDiskFile, &QAction::triggered, [ ]( ) {
		auto manage = AppInstance::getAppInstance( )->getAppDataManage( )->getAppMusicManage( );
		manage->deleteSelectMusicItem( );
	} );
	return true;
}
