#include "baseStackedWidget.h"

#include <source_location>
BaseStackedWidget::BaseStackedWidget( QWidget *parent ) : QStackedWidget( parent ), BaseClass( ) {
	setContextMenuPolicy( Qt::NoContextMenu );
}
BaseStackedWidget::BaseStackedWidget( ) : QStackedWidget( ), BaseClass( ) {
	setContextMenuPolicy( Qt::NoContextMenu );
}
