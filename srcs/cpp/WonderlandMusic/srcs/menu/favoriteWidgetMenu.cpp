#include "favoriteWidgetMenu.h"
#include "../application/appDataManage.h"

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
	return true;
}

bool FavoriteWidgetMenu::initAfter( ) {
	/*connect( addFavorite, &QAction::triggered, this, &FavoriteWidgetMenu::signal_add );
	connect( deleteFavorite, &QAction::triggered, this, &FavoriteWidgetMenu::signal_del );
	connect( changeFavorite, &QAction::triggered, this, &FavoriteWidgetMenu::signal_change );*/
	return true;
}

void FavoriteWidgetMenu::setLabelWidget( FavoriteItem *const label_widget ) {
	labelWidget = label_widget;
}
