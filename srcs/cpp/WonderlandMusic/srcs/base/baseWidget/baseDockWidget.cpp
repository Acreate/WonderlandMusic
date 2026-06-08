#include "baseDockWidget.h"

#include <source_location>
BaseDockWidget::BaseDockWidget( QWidget *parent ) : QDockWidget( parent ), BaseClass( ) {
	//setMouseTracking( true );
	setContextMenuPolicy( Qt::NoContextMenu );
}
BaseDockWidget::BaseDockWidget( ) : QDockWidget( ), BaseClass( ) {
}
