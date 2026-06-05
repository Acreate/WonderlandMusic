#include "topToolDockWidget.h"

#include <QPainter>

#include "../mainWindow.h"

#include "topToolWidget/topToolWidget.h"
TopToolDockWidget::TopToolDockWidget( MainWindow *parent ) : QDockWidget( parent ), mainWindow( parent ) {
	topToolWidget = new TopToolWidget( this );
	setWidget( topToolWidget );
	setContentsMargins( 0, 0, 0, 0 );
}
