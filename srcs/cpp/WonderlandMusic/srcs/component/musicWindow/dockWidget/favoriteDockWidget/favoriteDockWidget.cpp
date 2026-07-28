#include "favoriteDockWidget.h"

#include <component/musicWindow/musicWindow.h>

#include <head/release_macro.h>

#include "../../../../head/after_init_macro.h"
#include "../../../../head/before_init_macro.h"
#include "../../../../head/init_macro.h"

#include "../dockWidgetTitleWidget/dockWidgetTitleWidget.h"

#include "favoriteListWidget/favoriteListWidget.h"

FavoriteDockWidget::FavoriteDockWidget( MusicWindow *music_window ) : musicWindow( music_window ) {
}
FavoriteDockWidget::~FavoriteDockWidget( ) {
	deleteResource( );
}

bool FavoriteDockWidget::deleteResource( ) {
	musicWindow->removeDockWidget( this );
	setWidget( nullptr );
	Delete_Resource_App_Core_Ptr( dockWidgetTitleWidget );
	Delete_Resource_App_Core_Ptr( favoriteListWidget );
	return true;
}
bool FavoriteDockWidget::initBefore( ) {
	deleteResource( );
	favoriteListWidget = new FavoriteListWidget( this );
	dockWidgetTitleWidget = new DockWidgetTitleWidget( this );
	Before_Init_Resource_App_Core_Ptr( favoriteListWidget );
	Before_Init_Resource_App_Core_Ptr( dockWidgetTitleWidget );
	return true;
}
bool FavoriteDockWidget::init( ) {
	Init_Resource_App_Core_Ptr( favoriteListWidget );
	Init_Resource_App_Core_Ptr( dockWidgetTitleWidget );
	return true;
}
bool FavoriteDockWidget::initAfter( ) {
	After_Init_Resource_App_Core_Ptr( favoriteListWidget );
	After_Init_Resource_App_Core_Ptr( dockWidgetTitleWidget );
	setWidget( favoriteListWidget );
	setFloating( false );
	setContextMenuPolicy( Qt::NoContextMenu );
	musicWindow->addDockWidget( Qt::LeftDockWidgetArea, this );

	musicWindow->resizeDocks( { this }, { 200 }, Qt::Horizontal );

	return true;
}
void FavoriteDockWidget::updateDockSize( ) {
}
