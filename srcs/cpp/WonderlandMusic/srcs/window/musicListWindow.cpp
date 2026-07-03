#include "musicListWindow.h"

#include "../dockWidget/musicItemSizeInfoDockWidget.h"

#include "../scrollArea/musicContreScrollArea.h"

#include "../stackedWidget/musicListStackedWidget.h"

#include "../widget/musicContreWidget.h"

MusicContreScrollArea * MusicListWindow::findWidgetName( const QString &widget_name ) const {
	size_t count = musicContreScrollAreaVector.size( );
	if( count == 0 )
		return nullptr;
	auto data = musicContreScrollAreaVector.data( );
	size_t index;
	for( index = 0; index < count; index += 1 )
		if( data[ index ]->getWidgetName( ) == widget_name )
			return data[ index ];
	return nullptr;
}

MusicListWindow::MusicListWindow( QWidget *parent ) : QMainWindow( parent ) {
}

MusicListWindow::~MusicListWindow( ) {
	deleteResource( );
}

bool MusicListWindow::showWidget( const QString &widget_name ) {
	auto musicContreScrollArea = findWidgetName( widget_name );
	if( musicContreScrollArea == nullptr )
		return false;
	musicListStackedWidget->setCurrentWidget( musicContreScrollArea );
	return true;
}

bool MusicListWindow::createWidget( const QString &widget_name, const std::vector< MusicItem * > &load_music_items ) {
	auto musicContreScrollArea = findWidgetName( widget_name );
	if( musicContreScrollArea != nullptr )
		return false;
	musicContreScrollArea = new MusicContreScrollArea( musicListStackedWidget );
	musicListStackedWidget->addWidget( musicContreScrollArea );
	musicContreScrollArea->setItemWidth( musicItemSizeInfoDockWidget->getPlayerListTopWidget( ) );
	return true;
}

PlayerListTopWidget * MusicListWindow::getPlayerListTopWidget( ) const {
	return musicItemSizeInfoDockWidget->getPlayerListTopWidget( );
}

bool MusicListWindow::deleteResource( ) {
	disconnect( );
	Delete_Resource_App_Core_Ptr( musicItemSizeInfoDockWidget );
	Delete_Resource_App_Core_Ptr( musicListStackedWidget );
	musicContreScrollAreaVector.clear( );
	return true;
}

bool MusicListWindow::init( ) {
	deleteResource( );
	setWindowFlags( Qt::WindowType::Widget );
	musicItemSizeInfoDockWidget = new MusicItemSizeInfoDockWidget( this );
	musicListStackedWidget = new MusicListStackedWidget( this );

	if( musicItemSizeInfoDockWidget->init( ) == false )
		return false;
	if( musicListStackedWidget->init( ) == false )
		return false;
	setCentralWidget( musicListStackedWidget );
	return true;
}
