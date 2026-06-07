#include "musicCollectionScrollArea.h"

#include "widget/musicCollectionWidget.h"
MusicCollectionScrollArea::MusicCollectionScrollArea( QWidget *parent ) : QScrollArea( parent ) {
	setMouseTracking( true );
	setWidget( new MusicCollectionWidget( this ) );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setWidgetResizable( true );
}
