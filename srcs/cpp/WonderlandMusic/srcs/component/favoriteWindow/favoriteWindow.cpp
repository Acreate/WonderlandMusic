#include "favoriteWindow.h"

FavoriteWindow::FavoriteWindow( QWidget *parent ) : QMainWindow( parent ) {
}

FavoriteWindow::~FavoriteWindow( ) {
	deleteResource( );
}

void FavoriteWindow::updateItemInfo( FavoriteItem *favorite_item ) {
}

void FavoriteWindow::deleteItemInfo( FavoriteItem *favorite_item ) {
}

bool FavoriteWindow::deleteResource( ) {
	return true;
}

bool FavoriteWindow::initBefore( ) {
	return true;
}

bool FavoriteWindow::init( ) {
	return true;
}

bool FavoriteWindow::initAfter( ) {
	return true;
}

bool FavoriteWindow::getJsonData( QJsonObject &get_json_object ) const {
	return true;
}

bool FavoriteWindow::setJsonData( const QJsonObject &set_json_object ) {
	return true;
}
