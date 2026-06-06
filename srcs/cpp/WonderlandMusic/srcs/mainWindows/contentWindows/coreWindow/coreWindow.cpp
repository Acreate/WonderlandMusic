#include "coreWindow.h"

#include <QPainter>

#include "../contentWindow.h"

#include "coreStackedWidget/coreStackedWidget.h"
CoreWindow::CoreWindow( ContentWindow *parent ) : QMainWindow( parent ), contentWindow( parent ) {
	coreStackedWidget = new CoreStackedWidget( this );
	setCentralWidget( coreStackedWidget );
}
void CoreWindow::paintEvent( QPaintEvent *event ) {
	QMainWindow::paintEvent( event );
	QPainter painter( this );
	painter.fillRect( contentsRect( ), "#9932CC" );
}
size_t CoreWindow::triggerCoreStackedWidgetEvent( CoreStackedWidget *sender, const CoreStackedWidgetEventInfo &info ) {
	return 0;
}
