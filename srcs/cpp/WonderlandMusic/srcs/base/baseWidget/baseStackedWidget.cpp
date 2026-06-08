#include "baseStackedWidget.h"
BaseStackedWidget::BaseStackedWidget( QWidget *parent ) : QStackedWidget( parent ) {
	//setMouseTracking( true );
	setContextMenuPolicy( Qt::NoContextMenu );
}
