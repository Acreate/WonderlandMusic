#include "musicListScrollArea.h"

#include "widget/musicListWidget.h"
MusicListScrollArea::MusicListScrollArea( QWidget *parent ) : BaseScrollArea( parent ) {
	
	musicListWidget = new MusicListWidget( this );
	setWidget( musicListWidget );
}
