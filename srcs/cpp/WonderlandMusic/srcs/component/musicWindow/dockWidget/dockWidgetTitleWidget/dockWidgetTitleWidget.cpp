#include "dockWidgetTitleWidget.h"

#include <QDockWidget>
DockWidgetTitleWidget::DockWidgetTitleWidget( QDockWidget *parent ) : QWidget( parent ), dockWidget( parent ) {
}
DockWidgetTitleWidget::~DockWidgetTitleWidget( ) {
	deleteResource( );
}
bool DockWidgetTitleWidget::deleteResource( ) {
	if( dockWidget->titleBarWidget( ) == this )
		dockWidget->setTitleBarWidget( nullptr );
	return true;
}
bool DockWidgetTitleWidget::initBefore( ) {
	return true;
}
bool DockWidgetTitleWidget::init( ) {
	return true;
}
bool DockWidgetTitleWidget::initAfter( ) {
	dockWidget->setTitleBarWidget( this );
	return true;
}
