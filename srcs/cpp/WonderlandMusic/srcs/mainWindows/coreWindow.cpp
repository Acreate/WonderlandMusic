#include "coreWindow.h"

#include <QPainter>

#include "contentWindow.h"

#include "../stackedWidgets/coreStackedWidget.h"

CoreWindow::CoreWindow( ContentWindow *parent ) : BaseMainWindow( parent ), contentWindow( parent ) {

	coreStackedWidget = new CoreStackedWidget( this );
	setCentralWidget( coreStackedWidget );
}
