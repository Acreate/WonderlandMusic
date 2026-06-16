#include "topToolDockWidget.h"

#include <QPainter>

#include "../mainWindows/mainWindow.h"

#include "../widgets/topToolWidget.h"

TopToolDockWidget::TopToolDockWidget( MainWindow *parent ) : BaseDockWidget( parent ), mainWindow( parent ) {
	
	topToolWidget = new TopToolWidget( this );
	setWidget( topToolWidget );
	setContentsMargins( 0, 0, 0, 0 );
}
