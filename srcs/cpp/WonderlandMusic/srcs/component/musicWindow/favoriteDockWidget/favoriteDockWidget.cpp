#include "favoriteDockWidget.h"

#include "../musicWindow.h"

#include "../../../head/release_macro.h"

#include "../favoriteListWidget/favoriteListWidget.h"
FavoriteDockWidget::FavoriteDockWidget( MusicWindow *music_window ) : musicWindow( music_window ) {
}
FavoriteDockWidget::~FavoriteDockWidget( ) {
	deleteResource( );
}

bool FavoriteDockWidget::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( favoriteDockTitleWidget );
	Delete_Resource_App_Core_Ptr( favoriteListWidget );
	return true;
}
bool FavoriteDockWidget::initBefore( ) {
	deleteResource( );
	favoriteListWidget = new FavoriteListWidget( this );
	favoriteDockTitleWidget = new QWidget( this );
	return true;
}
bool FavoriteDockWidget::init( ) {
	return true;
}
bool FavoriteDockWidget::initAfter( ) {
	setTitleBarWidget( favoriteDockTitleWidget );
	setWidget( favoriteListWidget );

	setFloating( false );
	setDockLocation( Qt::LeftDockWidgetArea );
	musicWindow->addDockWidget( Qt::LeftDockWidgetArea, this );

	return true;
}
void FavoriteDockWidget::updateDockSize( ) {
	
}
