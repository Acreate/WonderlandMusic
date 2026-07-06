#include "favoritemDockWidget.h"

#include <QJsonObject>
#include <qevent.h>

#include "../application/appDataJsonKey.h"
#include "../application/appDataManage.h"
#include "../application/appInstance.h"
#include "../application/jsonKey/favoriteSrollAreaJsonKey.h"

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
	auto favoriteSrollAreaJsonKey = AppInstance::getAppInstance( )->getAppDataManage( )->getAppDataJsonKey( )->getFavoriteSrollArea( );
	get_json_object.insert( favoriteSrollAreaJsonKey->getWidth( ), this->width( ) );
	return true;
}

bool FavoritemDockWidget::setJsonData( const QJsonObject &set_json_object ) {
	auto favoriteSrollAreaJsonKey = AppInstance::getAppInstance( )->getAppDataManage( )->getAppDataJsonKey( )->getFavoriteSrollArea( );
	auto find = set_json_object.find( favoriteSrollAreaJsonKey->getWidth( ) );
	auto end = set_json_object.end( );
	if( find != end ) {
		qint64 integer = find.value( ).toInteger( );
		resize( integer, this->height( ) );
	}
	return true;
}

void FavoritemDockWidget::resizeEvent( QResizeEvent *event ) {
	QDockWidget::resizeEvent( event );
	qDebug( ) << "resizeEvent : " << event->size( );
}

void FavoritemDockWidget::showEvent( QShowEvent *event ) {
	QDockWidget::showEvent( event );
	qDebug( ) << "show : " << size( );
}
