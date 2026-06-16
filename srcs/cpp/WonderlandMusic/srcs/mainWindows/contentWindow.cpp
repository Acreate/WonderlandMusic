#include "contentWindow.h"

#include <QPainter>

#include "coreWindow.h"
#include "mainWindow.h"

#include "../dockWidgets/findDockWidget.h"
#include "../dockWidgets/playerDockWidget.h"

#include "../stackedWidgets/coreStackedWidget.h"

ContentWindow::ContentWindow( MainWindow *parent ) : BaseWidgetTypeMainWindow( parent ), mainWindow( parent ) {

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

	coreWindow = new BaseMainWindow( this );
	coreWindow->setWindowFlags( Qt::WindowType::Widget );
	setCentralWidget( coreWindow );
	auto coreStackedWidget = new CoreStackedWidget( coreWindow );
	setCentralWidget( coreStackedWidget );
}
