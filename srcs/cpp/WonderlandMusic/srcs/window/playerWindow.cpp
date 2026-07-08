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

FavoritemDockWidget * PlayerWindow::getFavoritemDockWidget( ) const {
	return favoritemDockWidget;
}

MusicListWindow * PlayerWindow::getMusicListWindow( ) const {
	return musicListWindow;
}

MusicControlDocWidget * PlayerWindow::getMusicControlDocWidget( ) const {
	return musicControlDocWidget;
}

bool PlayerWindow::deleteResource( ) {
	disconnect( );
	Delete_Resource_App_Core_Ptr( musicListWindow );
	Delete_Resource_App_Core_Ptr( musicControlDocWidget );
	Delete_Resource_App_Core_Ptr( favoritemDockWidget );
	return true;
}

bool PlayerWindow::init( ) {
	Init_Resource_App_Core_Ptr( musicListWindow );
	Init_Resource_App_Core_Ptr( favoritemDockWidget );
	Init_Resource_App_Core_Ptr( musicControlDocWidget );

	return true;
}

bool PlayerWindow::initBefore( ) {
	deleteResource( );
	setWindowFlags( Qt::WindowType::Widget );
	favoritemDockWidget = new FavoritemDockWidget( this );
	musicListWindow = new MusicListWindow( this );
	musicControlDocWidget = new MusicControlDocWidget( this );
	Before_Init_Resource_App_Core_Ptr( musicListWindow );
	Before_Init_Resource_App_Core_Ptr( favoritemDockWidget );
	Before_Init_Resource_App_Core_Ptr( musicControlDocWidget );
	return true;
}

bool PlayerWindow::initAfter( ) {
	After_Init_Resource_App_Core_Ptr( musicListWindow );
	After_Init_Resource_App_Core_Ptr( favoritemDockWidget );
	After_Init_Resource_App_Core_Ptr( musicControlDocWidget );
	setCentralWidget( musicListWindow );
	favoritemDockWidget->show( );
	musicControlDocWidget->show( );
	return true;
}

void PlayerWindow::resizeEvent( QResizeEvent *event ) {
	QMainWindow::resizeEvent( event );
}

bool PlayerWindow::getJsonData( QJsonObject &get_json_object ) const {
	musicListWindow->getJsonData( get_json_object );
	favoritemDockWidget->getJsonData( get_json_object );
	musicControlDocWidget->getJsonData( get_json_object );
	return true;
}

bool PlayerWindow::setJsonData( const QJsonObject &set_json_object ) {
	musicListWindow->setJsonData( set_json_object );
	favoritemDockWidget->setJsonData( set_json_object );
	musicControlDocWidget->setJsonData( set_json_object );
	return true;
}
