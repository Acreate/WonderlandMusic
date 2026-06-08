#include "musicListScrollArea.h"

#include "widget/musicListWidget.h"
MusicListScrollArea::MusicListScrollArea( QWidget *parent ) : BaseScrollArea( parent ) {

	setWidget( new MusicListWidget( this ) );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setWidgetResizable( true );
}
