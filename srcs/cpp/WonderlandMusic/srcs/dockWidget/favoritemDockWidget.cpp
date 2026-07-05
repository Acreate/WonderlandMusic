#include "favoritemDockWidget.h"

#include "../scrollArea/favoriteSrollArea.h"

#include "../widget/favoriteWidget.h"

#include "../window/playerWindow.h"

FavoritemDockWidget::FavoritemDockWidget( PlayerWindow *player_window ) : QDockWidget( player_window ), playerWindow( player_window ) {
}

FavoritemDockWidget::~FavoritemDockWidget( ) {
	deleteResource( );
}

FavoriteSrollArea * FavoritemDockWidget::getFavoriteSrollArea( ) const {
	return favoriteSrollArea;
}

bool FavoritemDockWidget::deleteResource( ) {
	disconnect( );
	playerWindow->removeDockWidget( this );
	Delete_Resource_App_Core_Ptr( titleBarWidget );
	Delete_Resource_App_Core_Ptr( favoriteSrollArea );
	return true;
}

bool FavoritemDockWidget::init( ) {
	Before_Init_Resource_App_Core_Ptr( favoriteSrollArea );
	Init_Resource_App_Core_Ptr( favoriteSrollArea );
	After_Init_Resource_App_Core_Ptr( favoriteSrollArea );

	return true;
}

bool FavoritemDockWidget::initBefore( ) {
	deleteResource( );
	setAllowedAreas( Qt::LeftDockWidgetArea );
	setContentsMargins( 0, 0, 0, 0 );
	titleBarWidget = new QWidget( this );
	favoriteSrollArea = new FavoriteSrollArea( this );
	return true;
}

bool FavoritemDockWidget::initAfter( ) {
	setTitleBarWidget( titleBarWidget );
	setWidget( favoriteSrollArea );
	playerWindow->addDockWidget( Qt::LeftDockWidgetArea, this );
	return true;
}
