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

bool PlayerWindow::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( musicListWindow );
	Delete_Resource_App_Core_Ptr( musicControlDocWidget );
	Delete_Resource_App_Core_Ptr( favoritemDockWidget );
	disconnect( );
	return true;
}

bool PlayerWindow::initWidget( ) {
	favoritemDockWidget = new FavoritemDockWidget( this );
	musicListWindow = new MusicListWindow( this );
	musicControlDocWidget = new MusicControlDocWidget( this );
	return true;
}

bool PlayerWindow::initMenu( ) {
	return true;
}

bool PlayerWindow::initConnect( ) {
	return true;
}

bool PlayerWindow::updateSubCompoment( ) {
	if( favoritemDockWidget->init( ) == false )
		return false;
	if( musicListWindow->init( ) == false )
		return false;
	if( musicControlDocWidget->init( ) == false )
		return false;
	return true;
}

bool PlayerWindow::init( ) {
	deleteResource( );

	setWindowFlags( Qt::WindowType::Widget );
	if( initWidget( ) == false )
		return false;
	if( initMenu( ) == false )
		return false;
	if( initConnect( ) == false )
		return false;
	if( updateSubCompoment( ) == false )
		return false;

	setCentralWidget( musicListWindow );
	return true;
}

bool PlayerWindow::getJsonData( QJsonObject &get_json_object ) const {
	return false;
}

bool PlayerWindow::setJsonData( const QJsonObject &set_json_object ) {
	return false;
}
