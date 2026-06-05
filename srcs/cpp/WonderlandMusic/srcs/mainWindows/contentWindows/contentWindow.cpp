#include "contentWindow.h"

#include <QPainter>

#include "../mainWindow.h"

#include "contentWidgetConpoment/findDockWidget.h"
#include "contentWidgetConpoment/playerDockWidget.h"

#include "coreWindow/coreWindow.h"

ContentWindow::ContentWindow( MainWindow *parent ) : QMainWindow( parent ), mainWindow( parent ) {

	Qt::DockWidgetArea dockWidgetArea;

	findDockWidget = new FindDockWidget( this );
	dockWidgetArea = Qt::DockWidgetArea::TopDockWidgetArea;
	findDockWidget->setFeatures( QDockWidget::NoDockWidgetFeatures );
	findDockWidget->setAllowedAreas( dockWidgetArea );
	addDockWidget( dockWidgetArea, findDockWidget );

	playerDockWidget = new PlayerDockWidget( this );
	dockWidgetArea = Qt::DockWidgetArea::BottomDockWidgetArea;
	playerDockWidget->setFeatures( QDockWidget::NoDockWidgetFeatures );
	playerDockWidget->setAllowedAreas( dockWidgetArea );
	addDockWidget( dockWidgetArea, playerDockWidget );

	coreWindow = new CoreWindow( this );
	coreWindow->setWindowFlags( Qt::WindowType::Widget );
	setCentralWidget( coreWindow );
}
