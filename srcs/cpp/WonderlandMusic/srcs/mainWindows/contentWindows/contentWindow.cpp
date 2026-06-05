#include "contentWindow.h"

#include <QPainter>

#include "../mainWindow.h"

#include "contentWidgetConpoment/findDockWidget.h"
#include "contentWidgetConpoment/playerDockWidget.h"

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

	setCentralWidget( new QWidget );
}
void ContentWindow::paintEvent( QPaintEvent *event ) {
	QMainWindow::paintEvent( event );

	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::GlobalColor::black );
}
