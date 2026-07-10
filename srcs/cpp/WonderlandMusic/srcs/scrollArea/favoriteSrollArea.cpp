#include "favoriteSrollArea.h"
#include <QJsonObject>
#include <QMouseEvent>
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

void FavoriteSrollArea::mousePressEvent( QMouseEvent *mouse_event ) {
	QScrollArea::mousePressEvent( mouse_event );
}

void FavoriteSrollArea::mouseReleaseEvent( QMouseEvent *mouse_event ) {
	QScrollArea::mouseReleaseEvent( mouse_event );
	auto mouseButton = mouse_event->button( );
	switch( mouseButton ) {
		case Qt::RightButton :
			emit signal_pop_menu( );
			break;
	}
}

void FavoriteSrollArea::mouseDoubleClickEvent( QMouseEvent *mouse_event ) {
	QScrollArea::mouseDoubleClickEvent( mouse_event );
}

bool FavoriteSrollArea::initBefore( ) {
	deleteResource( );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setWidgetResizable( true );
	favoriteWidget = new FavoriteWidget( this );
	Before_Init_Resource_App_Core_Ptr( favoriteWidget );
	return true;
}

bool FavoriteSrollArea::init( ) {
	Init_Resource_App_Core_Ptr( favoriteWidget );
	return true;
}

bool FavoriteSrollArea::initAfter( ) {
	After_Init_Resource_App_Core_Ptr( favoriteWidget );
	setWidget( favoriteWidget );
	return true;
}

bool FavoriteSrollArea::getJsonData( QJsonObject &get_json_object ) const {
	//favoriteWidget->getJsonData( get_json_object );
	auto jsonKey = AppInstance::getAppInstance( )->getAppDataManage( )->getAppDataJsonKey( )->getFavoriteSrollArea( );
	QJsonObject jsonObject;

	jsonObject.insert( jsonKey->getWidth( ), this->width( ) );
	jsonObject.insert( jsonKey->getHeight( ), this->height( ) );
	get_json_object.insert( jsonKey->getObjectName( ), jsonObject );
	return true;
}

bool FavoriteSrollArea::setJsonData( const QJsonObject &set_json_object ) {
	//favoriteWidget->setJsonData( set_json_object );
	if( set_json_object.empty( ) )
		return false;

	auto jsonKey = AppInstance::getAppInstance( )->getAppDataManage( )->getAppDataJsonKey( )->getFavoriteSrollArea( );
	auto find = set_json_object.find( jsonKey->getObjectName( ) );
	auto end = set_json_object.end( );
	if( find != end ) {
		auto jsonObject = find.value( ).toObject( );
		if( jsonObject.empty( ) == false ) {
			end = jsonObject.end( );
			qint64 width = this->width( );
			qint64 height = this->height( );
			find = jsonObject.find( jsonKey->getWidth( ) );
			if( find != end )
				width = find.value( ).toInteger( );
			find = jsonObject.find( jsonKey->getHeight( ) );
			if( find != end )
				height = find.value( ).toInteger( );
			resize( width, height );
		}
	}
	return true;
}
