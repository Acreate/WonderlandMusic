#include "baseWidget.h"

#include <source_location>

#include "../../applications/applicationInstance.h"
BaseWidget::BaseWidget( QWidget *parent ) : QWidget( parent ), BaseClass( ) {
	setContextMenuPolicy( Qt::NoContextMenu );
}
BaseWidget::BaseWidget( ) : BaseWidget( nullptr ) {
}
