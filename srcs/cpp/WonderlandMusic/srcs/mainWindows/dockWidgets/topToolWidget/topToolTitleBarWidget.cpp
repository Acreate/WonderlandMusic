#include "topToolTitleBarWidget.h"

#include "../topToolDockWidget.h"
TopToolTitleBarWidget::TopToolTitleBarWidget( TopToolDockWidget *parent ) : QWidget( parent ), topToolDockWidget( parent ) {
	setFixedSize( 0, 0 );
}
TopToolTitleBarWidget::~TopToolTitleBarWidget( ) { }
