#include "baseScrollArea.h"

#include <source_location>
BaseScrollArea::BaseScrollArea( QWidget *parent ) : QScrollArea( parent ), BaseClass( ) {
	//setMouseTracking( true );
	setContextMenuPolicy( Qt::NoContextMenu );
}
BaseScrollArea::BaseScrollArea( ) : QScrollArea( ), BaseClass( ) {
}
