#include "favoriteSrollArea.h"

#include <QJsonObject>

#include "../application/appDataJsonKey.h"
#include "../application/appDataManage.h"
#include "../application/appInstance.h"
#include "../application/appTranslate.h"
#include "../application/jsonKey/favoriteSrollAreaJsonKey.h"

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

bool FavoriteSrollArea::getJsonData( QJsonObject &get_json_object ) const {
	auto jsonKey = AppInstance::getAppInstance( )->getAppDataManage( )->getAppDataJsonKey( )->getFavoriteSrollArea( );
	int width = this->width( );
	get_json_object.insert( jsonKey->getWidth( ), width );
	return true;
}

bool FavoriteSrollArea::setJsonData( const QJsonObject &set_json_object ) {
	if( set_json_object.empty( ) )
		return false;

	auto jsonKey = AppInstance::getAppInstance( )->getAppDataManage( )->getAppDataJsonKey( )->getFavoriteSrollArea( );
	auto find = set_json_object.find( jsonKey->getWidth( ) );
	auto end = set_json_object.end( );
	if( find != end ) {
		qint64 width = find.value( ).toInteger( );
		resize( width, this->height( ) );
	}
	return true;
}
