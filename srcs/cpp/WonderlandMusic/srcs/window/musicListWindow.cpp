#include "musicListWindow.h"

#include "../dockWidget/musicItemSizeInfoDockWidget.h"

#include "../scrollArea/musicContreScrollArea.h"

#include "../widget/musicContreWidget.h"

MusicListWindow::MusicListWindow( QWidget *parent ) : QMainWindow( parent ) {
}

MusicListWindow::~MusicListWindow( ) {
	deleteResource( );
}

bool MusicListWindow::showFavorteMusicContreList( const QString &music_favorte_widget ) {
	return musicContreScrollArea->showFavorteMusicContreList( music_favorte_widget );
}

PlayerListTopWidget * MusicListWindow::getPlayerListTopWidget( ) const {
	return musicItemSizeInfoDockWidget->getPlayerListTopWidget( );
}

MusicContreWidget * MusicListWindow::getMusicContreWidget( ) const {
	return musicContreScrollArea->getMusicContreWidget( );
}

bool MusicListWindow::deleteResource( ) {
	disconnect( );
	Delete_Resource_App_Core_Ptr( musicItemSizeInfoDockWidget );
	Delete_Resource_App_Core_Ptr( musicContreScrollArea );
	return true;
}

bool MusicListWindow::getJsonData( QJsonObject &get_json_object ) const {
	return false;
}

bool MusicListWindow::setJsonData( const QJsonObject &set_json_object ) {
	return false;
}

bool MusicListWindow::init( ) {
	Before_Init_Resource_App_Core_Ptr( musicItemSizeInfoDockWidget );
	Before_Init_Resource_App_Core_Ptr( musicContreScrollArea );
	Init_Resource_App_Core_Ptr( musicItemSizeInfoDockWidget );
	Init_Resource_App_Core_Ptr( musicContreScrollArea );
	After_Init_Resource_App_Core_Ptr( musicItemSizeInfoDockWidget );
	After_Init_Resource_App_Core_Ptr( musicContreScrollArea );

	return true;
}

bool MusicListWindow::initBefore( ) {
	deleteResource( );
	setWindowFlags( Qt::WindowType::Widget );
	musicItemSizeInfoDockWidget = new MusicItemSizeInfoDockWidget( this );
	musicContreScrollArea = new MusicContreScrollArea( this );
	return true;
}

bool MusicListWindow::initAfter( ) {
	musicItemSizeInfoDockWidget->show( );
	setCentralWidget( musicContreScrollArea );
	return true;
}
