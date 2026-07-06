#include "favoritemDockWidget.h"

#include <QJsonObject>
#include <qevent.h>

#include "../application/appDataJsonKey.h"
#include "../application/appDataManage.h"
#include "../application/appInstance.h"
#include "../application/jsonKey/favoriteSrollAreaJsonKey.h"
#include "../application/jsonKey/favoritemDockWidgetJsonKey.h"

#include "../scrollArea/favoriteSrollArea.h"

#include "../widget/favoriteWidget.h"

#include "../window/playerWindow.h"

FavoritemDockWidget::FavoritemDockWidget( PlayerWindow *player_window ) : QDockWidget( player_window ), playerWindow( player_window ) {
}

FavoritemDockWidget::~FavoritemDockWidget( ) {
	deleteResource( );
}

FavoriteSrollArea * FavoritemDockWidget::getFavoriteSrollArea( ) const {
	return favoriteSrollArea;
}

bool FavoritemDockWidget::deleteResource( ) {
	disconnect( );
	playerWindow->removeDockWidget( this );
	Delete_Resource_App_Core_Ptr( titleBarWidget );
	Delete_Resource_App_Core_Ptr( favoriteSrollArea );
	return true;
}

bool FavoritemDockWidget::init( ) {
	Before_Init_Resource_App_Core_Ptr( favoriteSrollArea );
	Init_Resource_App_Core_Ptr( favoriteSrollArea );
	After_Init_Resource_App_Core_Ptr( favoriteSrollArea );

	return true;
}

bool FavoritemDockWidget::initBefore( ) {
	deleteResource( );
	setAllowedAreas( Qt::LeftDockWidgetArea );
	setContentsMargins( 0, 0, 0, 0 );
	titleBarWidget = new QWidget( this );
	favoriteSrollArea = new FavoriteSrollArea( this );
	return true;
}

bool FavoritemDockWidget::initAfter( ) {
	setTitleBarWidget( titleBarWidget );
	setWidget( favoriteSrollArea );
	playerWindow->addDockWidget( Qt::LeftDockWidgetArea, this );
	return true;
}

bool FavoritemDockWidget::getJsonData( QJsonObject &get_json_object ) const {
	favoriteSrollArea->getJsonData( get_json_object );
	auto jsonKey = AppInstance::getAppInstance( )->getAppDataManage( )->getAppDataJsonKey( )->getFavoritemDockWidget( );
	QJsonObject jsonObject;
	jsonObject.insert( jsonKey->getWidth( ), this->width( ) );
	get_json_object.insert( jsonKey->getObjectName( ), jsonObject );
	return true;
}

bool FavoritemDockWidget::setJsonData( const QJsonObject &set_json_object ) {
	favoriteSrollArea->setJsonData( set_json_object );
	if( set_json_object.empty( ) )
		return false;

	auto jsonKey = AppInstance::getAppInstance( )->getAppDataManage( )->getAppDataJsonKey( )->getFavoritemDockWidget( );
	auto find = set_json_object.find( jsonKey->getObjectName( ) );
	auto end = set_json_object.end( );
	if( find != end ) {
		auto jsonObject = find.value( ).toObject( );

		int width = this->width( );
		end = jsonObject.end( );
		find = jsonObject.find( jsonKey->getWidth( ) );
		if( find != end )
			width = find.value( ).toInteger( );
		playerWindow->resizeDocks( { this }, { width }, Qt::Horizontal );
	}

	return true;
}
