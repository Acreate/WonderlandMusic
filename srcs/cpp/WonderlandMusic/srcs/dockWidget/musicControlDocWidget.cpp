#include "musicControlDocWidget.h"

#include "../widget/playerToolsWidget.h"

#include "../window/playerWindow.h"

MusicControlDocWidget::MusicControlDocWidget( PlayerWindow *player_window ) : playerWindow( player_window ) {
}

bool MusicControlDocWidget::deleteResource( ) {
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
	setWidget( playerToolsWidget );

	playerWindow->addDockWidget( Qt::DockWidgetArea::BottomDockWidgetArea, this );
	return true;
}
