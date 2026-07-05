#include "favoriteSrollArea.h"

#include "../widget/favoriteWidget.h"

FavoriteSrollArea::FavoriteSrollArea( QWidget *parent ) : QScrollArea( parent ) {
}

FavoriteSrollArea::~FavoriteSrollArea( ) {
	deleteResource( );
}

FavoriteWidget * FavoriteSrollArea::getFavoriteWidget( ) const {
	return favoriteWidget;
}

bool FavoriteSrollArea::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( favoriteWidget );
	return true;
}

bool FavoriteSrollArea::initBefore( ) {
	deleteResource( );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setWidgetResizable( true );
	favoriteWidget = new FavoriteWidget( this );
	return true;
}

bool FavoriteSrollArea::init( ) {
	Before_Init_Resource_App_Core_Ptr( favoriteWidget );
	Init_Resource_App_Core_Ptr( favoriteWidget );
	After_Init_Resource_App_Core_Ptr( favoriteWidget );
	return true;
}

bool FavoriteSrollArea::initAfter( ) {
	setWidget( favoriteWidget );
	return true;
}
