#include "musicItemSizeInfoDockWidget.h"

#include <QScrollArea>
#include <QScrollBar>

#include "../widget/playerListTopWidget.h"

#include "../window/playerWindow.h"

MusicItemSizeInfoDockWidget::MusicItemSizeInfoDockWidget( PlayerWindow *player_window ) : QDockWidget( player_window ), playerWindow( player_window ) {
}

bool MusicItemSizeInfoDockWidget::deleteResource( ) {
	disconnect( );
	playerWindow->removeDockWidget( this );
	Delete_Resource_App_Core_Ptr( titleBarWidget );
	Delete_Resource_App_Core_Ptr( playerListTopWidget );
	Delete_Resource_App_Core_Ptr( playerListTopWidgetScrollArea );
	return true;
}

bool MusicItemSizeInfoDockWidget::init( ) {
	deleteResource( );

	playerListTopWidget = new PlayerListTopWidget( nullptr );
	if( playerListTopWidget->init( ) == false )
		return false;

	setAllowedAreas( Qt::TopDockWidgetArea );

	titleBarWidget = new QWidget( this );
	setTitleBarWidget( titleBarWidget );
	setContentsMargins( 0, 0, 0, 0 );

	playerListTopWidgetScrollArea = new QScrollArea( this );
	playerListTopWidgetScrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	playerListTopWidgetScrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	playerListTopWidgetScrollArea->setWidgetResizable( true );
	playerListTopWidgetScrollArea->setWindowFlags( Qt::WindowType::Widget );
	playerListTopWidgetScrollArea->verticalScrollBar( )->setEnabled( false );
	setWidget( playerListTopWidgetScrollArea );
	playerListTopWidget->setParent( playerListTopWidget );
	playerListTopWidgetScrollArea->setWidget( playerListTopWidget );

	playerWindow->addDockWidget( Qt::DockWidgetArea::TopDockWidgetArea, this );
	setFixedHeight( playerListTopWidget->height( ) );
	connect( playerListTopWidget, &PlayerListTopWidget::signal_changed_width, this, &MusicItemSizeInfoDockWidget::signal_changed_width );

	return true;
}
