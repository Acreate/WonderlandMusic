#include "favoriteWidget.h"

#include "../application/appDataManage.h"
#include "../application/appInstance.h"
#include "../application/translate/favoriteWidgetTranslate.h"

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
	auto appInstance = AppInstance::getAppInstance( );
	auto appDataManage = appInstance->getAppDataManage( );
	auto appTranslate = appDataManage->getTranslate( );
	auto favoriteWidgetTranslate = appTranslate->getFavoriteWidget( );
	auto &defautFavoriteName = favoriteWidgetTranslate->getDefautFavoriteName( );
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

bool FavoriteWidget::readJsonData( ) {
	return false;
}

bool FavoriteWidget::writeJsonData( ) {
	return false;
}
