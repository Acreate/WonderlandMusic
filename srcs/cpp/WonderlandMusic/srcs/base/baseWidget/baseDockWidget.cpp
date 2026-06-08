#include "baseDockWidget.h"

#include <source_location>
BaseDockWidget::BaseDockWidget( QWidget *parent ) : QDockWidget( parent ), BaseClass( ) {
	setFeatures( QDockWidget::NoDockWidgetFeatures );
	setContextMenuPolicy( Qt::NoContextMenu );
	setTitleBarWidget( new QWidget( this ) );
}
BaseDockWidget::BaseDockWidget( ) : BaseDockWidget( nullptr ) {
}
