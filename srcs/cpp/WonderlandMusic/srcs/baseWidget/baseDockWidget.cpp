#include "baseDockWidget.h"
BaseDockWidget::BaseDockWidget( QWidget *parent ) : QDockWidget( parent ) {
	//setMouseTracking( true );
	setContextMenuPolicy( Qt::NoContextMenu );
}
