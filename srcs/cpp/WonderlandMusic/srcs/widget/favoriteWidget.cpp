#include "favoriteWidget.h"

#include "../application/appDataManage.h"

#include "../window/playerWindow.h"

FavoriteWidget::FavoriteWidget( QWidget *parent ) : QWidget( parent ) {
}

bool FavoriteWidget::deleteResource( ) {
	disconnect( );
	return true;
}

FavoriteWidget::~FavoriteWidget( ) {
	deleteResource( );
}

bool FavoriteWidget::init( ) {
	deleteResource( );

	return true;
}

bool FavoriteWidget::initBefore( ) {
	return true;
}

bool FavoriteWidget::initAfter( ) {
	return true;
}

void FavoriteWidget::updateLayout( ) {
}

bool FavoriteWidget::appendFavoriteItem( const QString &create_favorite_name ) {
	return false;
}

bool FavoriteWidget::removeFavoriteItem( const QString &remove_favorite_name ) {
	return false;
}

bool FavoriteWidget::resetFavoriteItem( const std::vector<QString> &create_favorite_vector ) {
	return false;
}
