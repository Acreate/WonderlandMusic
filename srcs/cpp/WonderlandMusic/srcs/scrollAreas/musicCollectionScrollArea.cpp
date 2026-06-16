#include "musicCollectionScrollArea.h"

#include "../widgets/musicCollectionWidget.h"

MusicCollectionScrollArea::MusicCollectionScrollArea( QWidget *parent ) : BaseScrollArea( parent ) {

	musicCollectionWidget = new MusicCollectionWidget( this );
	setWidget( musicCollectionWidget );
}
MusicCollectionScrollArea::~MusicCollectionScrollArea( ) {
	delete musicCollectionWidget;
}
