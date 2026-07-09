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

MusicItemSizeInfoDockWidget * MusicListWindow::getMusicItemSizeInfoDockWidget( ) const {
	return musicItemSizeInfoDockWidget;
}

MusicContreScrollArea * MusicListWindow::getMusicContreScrollArea( ) const {
	return musicContreScrollArea;
}

bool MusicListWindow::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( musicItemSizeInfoDockWidget );
	Delete_Resource_App_Core_Ptr( musicContreScrollArea );
	return true;
}

bool MusicListWindow::getJsonData( QJsonObject &get_json_object ) const {
	musicItemSizeInfoDockWidget->getJsonData( get_json_object );
	musicContreScrollArea->getJsonData( get_json_object );
	return true;
}

bool MusicListWindow::setJsonData( const QJsonObject &set_json_object ) {
	musicItemSizeInfoDockWidget->setJsonData( set_json_object );
	musicContreScrollArea->setJsonData( set_json_object );
	return true;
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
