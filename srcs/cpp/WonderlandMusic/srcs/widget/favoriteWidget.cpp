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
