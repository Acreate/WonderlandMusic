#include "baseWidget.h"
BaseWidget::BaseWidget( QWidget *parent ) : QWidget( parent ) {
	//setMouseTracking( true );
	setContextMenuPolicy( Qt::NoContextMenu );
}
