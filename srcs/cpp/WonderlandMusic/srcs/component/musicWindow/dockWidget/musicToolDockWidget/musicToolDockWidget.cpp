#include "musicToolDockWidget.h"

#include "../../musicWindow.h"

#include "../../../../head/after_init_macro.h"
#include "../../../../head/before_init_macro.h"
#include "../../../../head/release_macro.h"

#include "../../../../tools/fontTools.h"

#include "../dockWidgetTitleWidget/dockWidgetTitleWidget.h"

#include "musicToolWidget/musicToolWidget.h"

MusicToolDockWidget::MusicToolDockWidget( MusicWindow *music_window ) : QDockWidget( music_window ), musicWindow( music_window ) {
}
MusicToolDockWidget::~MusicToolDockWidget( ) {
	deleteResource( );
}
bool MusicToolDockWidget::deleteResource( ) {
	musicWindow->removeDockWidget( this );
	setWidget( nullptr );
	Delete_Resource_App_Core_Ptr( dockWidgetTitleWidget );
	Delete_Resource_App_Core_Ptr( musicToolWidget );
	return true;
}
bool MusicToolDockWidget::initBefore( ) {
	deleteResource( );
	musicToolWidget = new MusicToolWidget( this );
	dockWidgetTitleWidget = new DockWidgetTitleWidget( this );
	Before_Init_Resource_App_Core_Ptr( musicToolWidget );
	Before_Init_Resource_App_Core_Ptr( dockWidgetTitleWidget );
	return true;
}
bool MusicToolDockWidget::init( ) {
	return true;
}
bool MusicToolDockWidget::initAfter( ) {
	After_Init_Resource_App_Core_Ptr( musicToolWidget );
	After_Init_Resource_App_Core_Ptr( dockWidgetTitleWidget );
	setWidget( musicToolWidget );
	setFloating( false );
	setDockLocation( Qt::LeftDockWidgetArea );
	setContextMenuPolicy( Qt::NoContextMenu );
	musicWindow->addDockWidget( Qt::BottomDockWidgetArea, this );
	int height;
	if( FontTools::getFontHeight( height ) == false )
		height = 28;
	musicWindow->resizeDocks( { this }, { height }, Qt::Vertical );
	return true;
}
