#include "favoriteWidget.h"

#include "../application/appDataManage.h"
#include "../application/appInstance.h"
#include "../application/translate/favoriteWidgetTranslate.h"

#include "../itemWidget/favoriteItemWidget.h"

#include "../window/playerWindow.h"

FavoriteWidget::FavoriteWidget( QWidget *parent ) : QWidget( parent ) {
}

bool FavoriteWidget::deleteResource( ) {
	disconnect( );
	Delete_Resource_App_Core_Ptr( rootFavoriteItemWidget );
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
	rootFavoriteItemWidget = new FavoriteItemWidget( this, defautFavoriteName );
	return true;
}

bool FavoriteWidget::craeteItem( const QString &item_name, FavoriteItemWidget *&result_create_item ) {
	size_t count = favoriteItemWidgetVector.size( );
	if( count ) {
		auto data = favoriteItemWidgetVector.data( );
		size_t index;
		for( index = 0; index < count; index += 1 )
			if( data[ index ]->name == item_name ) {
				result_create_item = data[ index ];
				return false;
			}
	}
	auto favoriteItemWidget = new FavoriteItemWidget( this, item_name );
	favoriteItemWidgetVector.emplace_back( favoriteItemWidget );
	favoriteItemWidget->show( );
	updateLayout( );
	result_create_item = favoriteItemWidget;
	return true;
}

bool FavoriteWidget::craeteItem( const QString &item_name, PlayerListWidget *item_widget, FavoriteItemWidget *&result_create_item ) {
	if( item_widget == nullptr )
		return craeteItem( item_name, result_create_item );

	size_t count = favoriteItemWidgetVector.size( );
	if( count ) {
		auto data = favoriteItemWidgetVector.data( );
		size_t index;
		for( index = 0; index < count; index += 1 )
			if( data[ index ]->name == item_name ) {
				result_create_item = data[ index ];
				return false;
			}
	}
	auto favoriteItemWidget = new FavoriteItemWidget( this, item_widget, item_name );
	favoriteItemWidgetVector.emplace_back( favoriteItemWidget );
	favoriteItemWidget->show( );
	updateLayout( );
	result_create_item = favoriteItemWidget;
	return true;
}

void FavoriteWidget::updateLayout( ) {
	size_t count = favoriteItemWidgetVector.size( );
	if( count == 0 )
		return;
	auto data = favoriteItemWidgetVector.data( );
	size_t index;
	int offsetY = 0;
	for( index = 0; index < count; index += 1 )
		if( data[ index ]->isHidden( ) == false ) {
			data[ index ]->adjustSize( );
			data[ index ]->move( 0, offsetY );
			offsetY += data[ index ]->height( );
		}
	setMinimumHeight( offsetY );
}

void FavoriteWidget::clearItem( ) {
}

FavoriteItemWidget * FavoriteWidget::getRootFavoriteItemWidget( ) const {
	return rootFavoriteItemWidget;
}

const std::vector< FavoriteItemWidget * > & FavoriteWidget::getFavoriteItemWidgetVector( ) const {
	return favoriteItemWidgetVector;
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
