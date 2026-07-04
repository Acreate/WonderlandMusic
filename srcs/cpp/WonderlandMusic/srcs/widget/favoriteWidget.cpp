#include "favoriteWidget.h"

#include "../application/appDataManage.h"
#include "../application/appInstance.h"

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

void FavoriteWidget::updateLayout( ) {
}

bool FavoriteWidget::getJsonData( QJsonObject &get_json_object ) const {
	return false;
}

bool FavoriteWidget::setJsonData( const QJsonObject &set_json_object ) {
	return false;
}
