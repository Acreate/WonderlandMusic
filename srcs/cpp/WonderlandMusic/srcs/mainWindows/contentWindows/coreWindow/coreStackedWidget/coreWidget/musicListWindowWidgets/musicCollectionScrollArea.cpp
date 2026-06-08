#include "musicCollectionScrollArea.h"

#include "widget/musicCollectionWidget.h"
MusicCollectionScrollArea::MusicCollectionScrollArea( QWidget *parent ) : BaseScrollArea( parent ) {
	setWidget( new MusicCollectionWidget( this ) );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setWidgetResizable( true );
}
