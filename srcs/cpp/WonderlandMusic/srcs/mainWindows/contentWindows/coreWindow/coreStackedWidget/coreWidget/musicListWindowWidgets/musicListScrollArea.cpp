#include "musicListScrollArea.h"

#include "widget/musicListWidget.h"
MusicListScrollArea::MusicListScrollArea( QWidget *parent ) : QScrollArea( parent ) {
	setMouseTracking( true );
	setWidget( new MusicListWidget( this ) );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setWidgetResizable( true );
}
