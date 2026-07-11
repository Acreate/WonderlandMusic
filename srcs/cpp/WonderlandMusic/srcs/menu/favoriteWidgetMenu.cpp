#include "favoriteWidgetMenu.h"
#include "../application/appDataManage.h"
#include "../application/appInstance.h"
#include "../application/appMusicManage.h"
#include "../application/translate/favoriteWidgetMenuTranslate.h"
#include "../widget/favoriteWidget.h"
#include "../window/playerWindow.h"

FavoriteWidgetMenu::FavoriteWidgetMenu( ) {
}

FavoriteWidgetMenu::~FavoriteWidgetMenu( ) {
}

bool FavoriteWidgetMenu::deleteResource( ) {
	clear( );
	return true;
}

FavoriteItem * FavoriteWidgetMenu::getLabelWidget( ) const {
	return labelWidget;
}

bool FavoriteWidgetMenu::initBefore( ) {
	deleteResource( );

	return true;
}

bool FavoriteWidgetMenu::init( ) {
	auto translate = AppInstance::getAppInstance( )->getAppDataManage( )->getTranslate( )->getFavoriteWidgetMenu( );
	addFavorite = addAction( translate->getAddFavorite( ) );
	deleteFavorite = addAction( translate->getDeleteFavorite( ) );
	changeFavorite = addAction( translate->getChangeFavorite( ) );
	return true;
}

bool FavoriteWidgetMenu::initAfter( ) {
	connect( addFavorite, &QAction::triggered, this, &FavoriteWidgetMenu::signal_add );
	connect( deleteFavorite, &QAction::triggered, this, &FavoriteWidgetMenu::signal_del );
	connect( changeFavorite, &QAction::triggered, this, &FavoriteWidgetMenu::signal_change );
	return true;
}

void FavoriteWidgetMenu::setLabelWidget( FavoriteItem *const label_widget ) {
	labelWidget = label_widget;
	auto favoriteItem = AppInstance::getAppInstance( )->getAppDataManage( )->getAppMusicManage( )->getRootItem( );
	bool enable = false;
	if( favoriteItem == label_widget ) {
		deleteFavorite->setEnabled( enable );
		changeFavorite->setEnabled( enable );
	} else {
		enable = label_widget != nullptr;
		deleteFavorite->setEnabled( enable );
		changeFavorite->setEnabled( enable );
	}
}
