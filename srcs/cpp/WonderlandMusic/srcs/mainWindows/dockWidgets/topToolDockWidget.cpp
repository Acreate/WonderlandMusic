#include "topToolDockWidget.h"

#include <QPainter>

#include "../mainWindow.h"

#include "topToolWidget/topToolWidget.h"
TopToolDockWidget::TopToolDockWidget( MainWindow *parent ) : QDockWidget( parent ), mainWindow( parent ) {
	topToolWidget = new TopToolWidget( this );
	setWidget( topToolWidget );
	setContentsMargins( 0, 0, 0, 0 );
}
size_t TopToolDockWidget::triggerTopToolWidgetEvent( TopToolWidget *sender, const TopToolWidgetEventInfo &info ) {
	auto topToolDockEventInfo = TopToolDockWidgetEventInfo( );
	topToolDockEventInfo.eventType = TopToolDockWidgetEventInfo::EventType::TopToolEvent;
	TopToolDockWidgetEventInfo::TopToolEventData topData( sender, &info );
	topToolDockEventInfo.topToolEventData = &topData;
	return TopToolDockEventClassName::triggerTopToolDockWidgetEvent( mainWindow, this, topToolDockEventInfo );
}
