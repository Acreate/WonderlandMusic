#include "musicControlDocWidget.h"

#include "../widget/playerToolsWidget.h"

#include "../window/playerWindow.h"

MusicControlDocWidget::MusicControlDocWidget( PlayerWindow *player_window ) : playerWindow( player_window ) {
}

bool MusicControlDocWidget::deleteResource( ) {
	disconnect( );
	playerWindow->removeDockWidget( this );
	Delete_Resource_App_Core_Ptr( titleBarWidget );
	Delete_Resource_App_Core_Ptr( playerToolsWidget );
	return true;
}

bool MusicControlDocWidget::init( ) {
	deleteResource( );
	setAllowedAreas( Qt::BottomDockWidgetArea );
	setContentsMargins( 0, 0, 0, 0 );

	titleBarWidget = new QWidget( this );
	setTitleBarWidget( titleBarWidget );

	playerToolsWidget = new PlayerToolsWidget( this );

	Before_Init_Resource_App_Core_Ptr( playerToolsWidget );
	Init_Resource_App_Core_Ptr( playerToolsWidget );
	After_Init_Resource_App_Core_Ptr( playerToolsWidget );

	setWidget( playerToolsWidget );

	playerWindow->addDockWidget( Qt::DockWidgetArea::BottomDockWidgetArea, this );
	return true;
}

bool MusicControlDocWidget::initBefore( ) {
	return true;
}

bool MusicControlDocWidget::initAfter( ) {
	return true;
}
