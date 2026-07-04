#include "favoritemDockWidget.h"

#include "../widget/favoriteWidget.h"

#include "../window/playerWindow.h"

FavoritemDockWidget::FavoritemDockWidget( PlayerWindow *player_window ) : QDockWidget( player_window ), playerWindow( player_window ) {
}

bool FavoritemDockWidget::deleteResource( ) {
	disconnect( );
	playerWindow->removeDockWidget( this );
	Delete_Resource_App_Core_Ptr( titleBarWidget );
	Delete_Resource_App_Core_Ptr( favoriteWidget );
	return true;
}

bool FavoritemDockWidget::init( ) {
	deleteResource( );
	favoriteWidget = new FavoriteWidget( this );

	Before_Init_Resource_App_Core_Ptr( favoriteWidget );
	Init_Resource_App_Core_Ptr( favoriteWidget );
	After_Init_Resource_App_Core_Ptr( favoriteWidget );
	setAllowedAreas( Qt::LeftDockWidgetArea );
	setContentsMargins( 0, 0, 0, 0 );
	titleBarWidget = new QWidget( this );
	setTitleBarWidget( titleBarWidget );

	playerWindow->addDockWidget( Qt::LeftDockWidgetArea, this );
	return true;
}

bool FavoritemDockWidget::initBefore( ) {
	return true;
}

bool FavoritemDockWidget::initAfter( ) {
	return true;
}
