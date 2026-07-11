#include "addFavoriteItemWidget.h"

AddFavoriteItemWidget::AddFavoriteItemWidget( QWidget *parent ) : QWidget( parent ) {
}

AddFavoriteItemWidget::~AddFavoriteItemWidget( ) {
	deleteResource( );
}

bool AddFavoriteItemWidget::deleteResource( ) {
	return true;
}

bool AddFavoriteItemWidget::initBefore( ) {
	return true;
}

bool AddFavoriteItemWidget::init( ) {
	return true;
}

bool AddFavoriteItemWidget::initAfter( ) {
	return true;
}
