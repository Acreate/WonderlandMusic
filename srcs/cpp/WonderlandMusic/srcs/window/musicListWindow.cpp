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

bool MusicListWindow::deleteResource( ) {
	disconnect( );
	Delete_Resource_App_Core_Ptr( musicItemSizeInfoDockWidget );
	Delete_Resource_App_Core_Ptr( musicContreScrollArea );
	return true;
}

bool MusicListWindow::init( ) {
	deleteResource( );
	setWindowFlags( Qt::WindowType::Widget );
	musicItemSizeInfoDockWidget = new MusicItemSizeInfoDockWidget( this );
	musicContreScrollArea = new MusicContreScrollArea( this );

	if( musicItemSizeInfoDockWidget->init( ) == false )
		return false;
	if( musicContreScrollArea->init( ) == false )
		return false;
	setCentralWidget( musicContreScrollArea );
	return true;
}
