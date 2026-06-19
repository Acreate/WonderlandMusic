#include "playerWidgetMenu.h"

#include "../application/appInstance.h"
#include "../application/appTranslate.h"
#include "../application/musicDecoder.h"

#include "../widget/playerListWidget.h"

PlayerWidgetMenu::PlayerWidgetMenu( PlayerListWidget *player_list_widget ) : QMenu( player_list_widget ), playerListWidget( player_list_widget ) {
}

bool PlayerWidgetMenu::initVar( ) {
	if( playerListWidget == nullptr )
		return false;
	appInstance = AppInstance::getAppInstance( );
	if( appInstance == nullptr )
		return false;
	appTranslate = appInstance->getTranslate( );
	if( appTranslate == nullptr )
		return false;
	musicDecoder = appInstance->getMusicDecoder( );
	if( musicDecoder == nullptr )
		return false;
	return true;
}

bool PlayerWidgetMenu::initSubMenu( ) {
	playerMenu = addMenu( appTranslate->getPlayerListMenuenuPlayerMenu( ) );

	removeMenu = addMenu( appTranslate->getPlayerListMenuMoveMenu( ) );
	controlMenu = addMenu( appTranslate->getPlayerListMenuControlMenu( ) );
	return true;
}

bool PlayerWidgetMenu::initSubMenuAcction( ) {
	setplay = playerMenu->QWidget::addAction( appTranslate->getPlayerListMenuPlayerMenuSetCurrentPlayAction( ) );
	insterPlay = playerMenu->QWidget::addAction( appTranslate->getPlayerListMenuPlayerMenuInsterCurrentPlayAction( ) );

	moveTop = controlMenu->QWidget::addAction( appTranslate->getPlayerListMenuControlMenuMoveTopMusicAction( ) );
	moveBottom = controlMenu->QWidget::addAction( appTranslate->getPlayerListMenuControlMenuMoveBottomMusicAction( ) );

	removeMusic = removeMenu->QWidget::addAction( appTranslate->getPlayerListMenuControlMenuRemoveMusicAction( ) );
	removeMusic = removeMenu->QWidget::addAction( appTranslate->getPlayerListMenuControlMenuDeleteMusicAction( ) );
	return true;
}

bool PlayerWidgetMenu::initConnectAcction( ) {
	return true;
}

bool PlayerWidgetMenu::init( ) {
	clear( );
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
	std::vector< MusicInfoItemWidget * > selectVector;
	playerListWidget->getSelectItemWidgetVector( selectVector );
	musicDecoder->setCurrentSelectPlay( selectVector );
}

void PlayerWidgetMenu::insterCurrentSelectPlay( ) {
	std::vector< MusicInfoItemWidget * > selectVector;
	playerListWidget->getSelectItemWidgetVector( selectVector );
	musicDecoder->insterCurrentSelectPlay( selectVector );
}

void PlayerWidgetMenu::removePlayListSelectInfo( ) {
	std::vector< MusicInfoItemWidget * > selectVector;
	playerListWidget->getSelectItemWidgetVector( selectVector );
	musicDecoder->removePlayListSelectInfo( selectVector );
}

void PlayerWidgetMenu::deletePlayListSelectFile( ) {
	std::vector< MusicInfoItemWidget * > selectVector;
	playerListWidget->getSelectItemWidgetVector( selectVector );
	musicDecoder->deletePlayListSelectFile( selectVector );
}

void PlayerWidgetMenu::selectListMoveTop( ) {
	std::vector< MusicInfoItemWidget * > selectVector;
	playerListWidget->getSelectItemWidgetVector( selectVector );
	musicDecoder->selectListMoveTop( selectVector );
}

void PlayerWidgetMenu::selectListMoveBottom( ) {
	std::vector< MusicInfoItemWidget * > selectVector;
	playerListWidget->getSelectItemWidgetVector( selectVector );
	musicDecoder->selectListMoveBottom( selectVector );
}
