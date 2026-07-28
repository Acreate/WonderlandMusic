#include "favoriteListWidget.h"
FavoriteListWidget::FavoriteListWidget( QWidget *parent ) : QWidget( parent ) {
}
FavoriteListWidget::~FavoriteListWidget( ) {
	deleteResource( );
}
bool FavoriteListWidget::deleteResource( ) {
	return true;
}
bool FavoriteListWidget::initBefore( ) {
	deleteResource( );
	return true;
}
bool FavoriteListWidget::init( ) {
	return true;
}
bool FavoriteListWidget::initAfter( ) {
	return true;
}
