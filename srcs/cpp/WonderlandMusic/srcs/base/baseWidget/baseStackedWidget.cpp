#include "baseStackedWidget.h"

#include <source_location>
BaseStackedWidget::BaseStackedWidget( QWidget *parent ) : QStackedWidget( parent ), BaseClass( ) {
	//setMouseTracking( true );
	setContextMenuPolicy( Qt::NoContextMenu );
}
BaseStackedWidget::BaseStackedWidget( ) : QStackedWidget( ), BaseClass( ) {
}
