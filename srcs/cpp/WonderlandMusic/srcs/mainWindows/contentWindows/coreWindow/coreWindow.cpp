#include "coreWindow.h"

#include <QPainter>

#include "../contentWindow.h"

#include "coreStackedWidget/coreStackedWidget.h"
CoreWindow::CoreWindow( ContentWindow *parent ) : BaseMainWindow( parent ), contentWindow( parent ) {
	coreStackedWidget = new CoreStackedWidget( this );
	setCentralWidget( coreStackedWidget );
}
