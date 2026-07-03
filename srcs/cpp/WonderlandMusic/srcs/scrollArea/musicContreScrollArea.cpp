#include "musicContreScrollArea.h"

#include "../widget/musicContreWidget.h"

MusicContreScrollArea::MusicContreScrollArea( QWidget *parent ) : QScrollArea( parent ) {
}

bool MusicContreScrollArea::deleteResource( ) {
	disconnect( );
	Delete_Resource_App_Core_Ptr( musicContreWidget );
	return true;
}

bool MusicContreScrollArea::init( ) {
	deleteResource( );
	musicContreWidget = new MusicContreWidget( this );
	return true;
}
