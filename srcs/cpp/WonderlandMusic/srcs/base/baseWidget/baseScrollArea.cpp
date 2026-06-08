#include "baseScrollArea.h"

#include <QScrollBar>
#include <source_location>
BaseScrollArea::BaseScrollArea( QWidget *parent ) : QScrollArea( parent ), BaseClass( ) {
	setContextMenuPolicy( Qt::NoContextMenu );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	verticalScrollBar( )->setContextMenuPolicy( Qt::NoContextMenu );
	horizontalScrollBar( )->setContextMenuPolicy( Qt::NoContextMenu );
	setWidgetResizable( true );
}
BaseScrollArea::BaseScrollArea( ) : QScrollArea( ), BaseClass( ) {
	setContextMenuPolicy( Qt::NoContextMenu );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	verticalScrollBar( )->setContextMenuPolicy( Qt::NoContextMenu );
	horizontalScrollBar( )->setContextMenuPolicy( Qt::NoContextMenu );
	setWidgetResizable( true );
}
