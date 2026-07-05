#include "playerWindow.h"
#include <QJsonObject>
#include <qevent.h>

#include "musicListWindow.h"

#include "../dockWidget/favoritemDockWidget.h"
#include "../dockWidget/musicControlDocWidget.h"
#include "../mutex/userMutex.h"

#include "../tools/pathTools.h"
#include "../widget/musicContreWidget.h"

PlayerWindow::~PlayerWindow( ) {
	deleteResource( );
}

PlayerWindow::PlayerWindow( QWidget *parent ) : QMainWindow( parent ) {
}

PlayerListTopWidget * PlayerWindow::getPlayerListTopWidget( ) const {
	return musicListWindow->getPlayerListTopWidget( );
}

FavoriteWidget * PlayerWindow::getFavoriteWidget( ) const {
	return favoritemDockWidget->getFavoriteWidget( );
}

MusicContreWidget * PlayerWindow::getMusicContreWidget( ) const {
	return musicListWindow->getMusicContreWidget( );
}

bool PlayerWindow::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( musicListWindow );
	Delete_Resource_App_Core_Ptr( musicControlDocWidget );
	Delete_Resource_App_Core_Ptr( favoritemDockWidget );
	disconnect( );
	return true;
}

bool PlayerWindow::init( ) {
	Before_Init_Resource_App_Core_Ptr( favoritemDockWidget );
	Before_Init_Resource_App_Core_Ptr( musicListWindow );
	Before_Init_Resource_App_Core_Ptr( musicControlDocWidget );

	Init_Resource_App_Core_Ptr( favoritemDockWidget );
	Init_Resource_App_Core_Ptr( musicListWindow );
	Init_Resource_App_Core_Ptr( musicControlDocWidget );

	After_Init_Resource_App_Core_Ptr( favoritemDockWidget );
	After_Init_Resource_App_Core_Ptr( musicListWindow );
	After_Init_Resource_App_Core_Ptr( musicControlDocWidget );

	setCentralWidget( musicListWindow );
	return true;
}

bool PlayerWindow::initBefore( ) {
	deleteResource( );

	setWindowFlags( Qt::WindowType::Widget );

	favoritemDockWidget = new FavoritemDockWidget( this );
	musicListWindow = new MusicListWindow( this );
	musicControlDocWidget = new MusicControlDocWidget( this );
	favoritemDockWidget->show( );
	musicControlDocWidget->show( );
	return true;
}

bool PlayerWindow::initAfter( ) {
	return true;
}

bool PlayerWindow::getJsonData( QJsonObject &get_json_object ) const {
	return false;
}

bool PlayerWindow::setJsonData( const QJsonObject &set_json_object ) {
	return false;
}
