#include "musicCollectionScrollArea.h"

#include "widget/musicCollectionWidget.h"
MusicCollectionScrollArea::MusicCollectionScrollArea( QWidget *parent ) : BaseScrollArea( parent ) {

	musicCollectionWidget = new MusicCollectionWidget( this );
	setWidget( musicCollectionWidget );
}
MusicCollectionScrollArea::~MusicCollectionScrollArea( ) {
	delete musicCollectionWidget;
}
