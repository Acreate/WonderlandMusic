#include "baseScrollArea.h"
BaseScrollArea::BaseScrollArea( QWidget *parent ) : QScrollArea( parent ) {
	//setMouseTracking( true );
	setContextMenuPolicy( Qt::NoContextMenu );
}
