#include "musicTitleDockWidget.h"

#include <QScrollArea>

#include "../../musicWindow.h"

#include "../../../../head/after_init_macro.h"
#include "../../../../head/before_init_macro.h"
#include "../../../../head/init_macro.h"
#include "../../../../head/release_macro.h"

#include "../dockWidgetTitleWidget/dockWidgetTitleWidget.h"

#include "musicTitleWidget/musicTitleWidget.h"

#include "titleVerticalScrollBar/titleVerticalScrollBar.h"
MusicTitleDockWidget::MusicTitleDockWidget( MusicWindow *music_window ) : QDockWidget( music_window ), musicWindow( music_window ) {
}
MusicTitleDockWidget::~MusicTitleDockWidget( ) {
	deleteResource( );
}
bool MusicTitleDockWidget::deleteResource( ) {
	musicWindow->removeDockWidget( this );
	setWidget( nullptr );
	Delete_Resource_App_Core_Ptr( dockWidgetTitleWidget );
	Delete_Resource_App_Core_Ptr( musicTitileScrollArea );
	return true;
}
bool MusicTitleDockWidget::initBefore( ) {
	deleteResource( );
	verticalScrollBar = new TitleVerticalScrollBar( this );
	musicTitileScrollArea = new QScrollArea( this );
	musicTitleWidget = new MusicTitleWidget( this );
	dockWidgetTitleWidget = new DockWidgetTitleWidget( this );
	Before_Init_Resource_App_Core_Ptr( musicTitleWidget );
	Before_Init_Resource_App_Core_Ptr( dockWidgetTitleWidget );
	return true;
}
bool MusicTitleDockWidget::init( ) {
	Init_Resource_App_Core_Ptr( musicTitleWidget );
	Init_Resource_App_Core_Ptr( dockWidgetTitleWidget );
	return true;
}
bool MusicTitleDockWidget::initAfter( ) {
	After_Init_Resource_App_Core_Ptr( musicTitleWidget );
	After_Init_Resource_App_Core_Ptr( dockWidgetTitleWidget );
	musicTitileScrollArea->setVerticalScrollBar( verticalScrollBar );
	musicTitileScrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	musicTitileScrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	musicTitileScrollArea->setWidget( musicTitleWidget );
	setWidget( musicTitileScrollArea );
	setFloating( false );
	setContextMenuPolicy( Qt::NoContextMenu );
	musicWindow->addDockWidget( Qt::TopDockWidgetArea, this );
	return true;
}
