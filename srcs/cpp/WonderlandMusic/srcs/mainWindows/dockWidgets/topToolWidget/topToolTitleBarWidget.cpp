#include "topToolTitleBarWidget.h"

#include "../topToolDockWidget.h"
TopToolTitleBarWidget::TopToolTitleBarWidget( TopToolDockWidget *parent ) : BaseWidget( parent ), topToolDockWidget( parent ) {
	setFixedSize( 0, 0 );
}
TopToolTitleBarWidget::~TopToolTitleBarWidget( ) { }
