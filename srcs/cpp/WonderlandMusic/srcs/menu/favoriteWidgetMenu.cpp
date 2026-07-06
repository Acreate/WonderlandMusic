#include "favoriteWidgetMenu.h"

#include "../application/appDataManage.h"
#include "../application/appInstance.h"
#include "../application/appUserInterfaceManage.h"
#include "../application/translate/favoriteWidgetMenuTranslate.h"

#include "../dockWidget/favoritemDockWidget.h"

#include "../scrollArea/favoriteSrollArea.h"

#include "../stackedWidget/mainStackedWidget.h"

#include "../tools/widgetTools.h"

#include "../widget/favoriteWidget.h"

#include "../window/mainWindow.h"
#include "../window/playerWindow.h"

FavoriteWidgetMenu::FavoriteWidgetMenu( ) {
}

FavoriteWidgetMenu::~FavoriteWidgetMenu( ) {
}

bool FavoriteWidgetMenu::deleteResource( ) {
	clear( );
	return true;
}

FavoriteItemWidget * FavoriteWidgetMenu::getLabelWidget( ) const {
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

	auto interfaceManage = AppInstance::getAppInstance( )->getAppUserInterfaceManage( );
	auto favoriteWidget = interfaceManage->getMainWindow( )->getMainStackedWidget( )->getPlayerWindow( )->getFavoritemDockWidget( )->getFavoriteSrollArea( )->getFavoriteWidget( );
	connect( favoriteWidget, &FavoriteWidget::signal_favorite_Item_pop_menu, this, [this] ( FavoriteItemWidget *label_widget ) {
		labelWidget = label_widget;
		QPoint suggestPos;
		bool result = WidgetTools::getMenuSuggestionShowMenuPos( suggestPos, QCursor::pos( ), this );
		if( result )
			exec( suggestPos );
	} );
	return true;
}
