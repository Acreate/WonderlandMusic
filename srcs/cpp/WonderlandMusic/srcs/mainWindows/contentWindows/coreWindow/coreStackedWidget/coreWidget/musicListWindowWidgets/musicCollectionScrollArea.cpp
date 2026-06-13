#include "musicCollectionScrollArea.h"

#include "MusicCollectionWidget/musicCollectionWidget.h"
MusicCollectionScrollArea::MusicCollectionScrollArea( QWidget *parent ) : BaseScrollArea( parent ) {

	musicCollectionWidget = new MusicCollectionWidget( this );
	setWidget( musicCollectionWidget );
}
MusicCollectionScrollArea::~MusicCollectionScrollArea( ) {
	delete musicCollectionWidget;
}
