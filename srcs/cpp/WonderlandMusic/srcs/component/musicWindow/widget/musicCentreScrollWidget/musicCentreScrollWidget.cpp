#include "musicCentreScrollWidget.h"

#include "../../musicWindow.h"

#include "../../../../head/after_init_macro.h"
#include "../../../../head/before_init_macro.h"
#include "../../../../head/init_macro.h"
#include "../../../../head/release_macro.h"

#include "musicCentreWidget/musicCentreWidget.h"

MusicCentreScrollWidget::MusicCentreScrollWidget( MusicWindow *music_window ) : QScrollArea( music_window ), musicWindow( music_window ) {
}
MusicCentreScrollWidget::~MusicCentreScrollWidget( ) {
	deleteResource( );
}
bool MusicCentreScrollWidget::deleteResource( ) {
	if( musicWindow->centralWidget( ) == this )
		musicWindow->takeCentralWidget( );
	setWidget( nullptr );
	Delete_Resource_App_Core_Ptr( musicCentreWidget );
	return true;
}
bool MusicCentreScrollWidget::initBefore( ) {
	deleteResource( );
	musicCentreWidget = new MusicCentreWidget( musicWindow );
	Before_Init_Resource_App_Core_Ptr( musicCentreWidget );
	return true;
}
bool MusicCentreScrollWidget::init( ) {
	Init_Resource_App_Core_Ptr( musicCentreWidget );
	return true;
}
bool MusicCentreScrollWidget::initAfter( ) {
	After_Init_Resource_App_Core_Ptr( musicCentreWidget );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setWidgetResizable( true );
	setWidget( musicCentreWidget );
	musicWindow->setCentralWidget( this );
	return true;
}
