#include "favoriteWindow.h"

FavoriteWindow::FavoriteWindow( QWidget *parent ): QMainWindow( parent ) {
}

FavoriteWindow::~FavoriteWindow( ) {
	deleteResource( );
}

void FavoriteWindow::updateItemInfo( FavoriteItem *favorite_item ) {
	
}

void FavoriteWindow::deleteItemInfo( FavoriteItem *favorite_item ) {
}

bool FavoriteWindow::deleteResource( ) {
	return false;
}

bool FavoriteWindow::initBefore( ) {
	return false;
}

bool FavoriteWindow::init( ) {
	return false;
}

bool FavoriteWindow::initAfter( ) {
	return false;
}

bool FavoriteWindow::getJsonData( QJsonObject &get_json_object ) const {
	return false;
}

bool FavoriteWindow::setJsonData( const QJsonObject &set_json_object ) {
	return false;
}
