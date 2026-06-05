#include "topToolDockWidget.h"

#include <QPainter>

#include "../mainWindow.h"

#include "topToolWidget/topToolWidget.h"
TopToolDockWidget::TopToolDockWidget( MainWindow *parent ) : QDockWidget( parent ), mainWindow( parent ) {
	topToolWidget = new TopToolWidget( this );
	setWidget( topToolWidget );
	setContentsMargins( 0, 0, 0, 0 );
}
size_t TopToolDockWidget::triggerTopToolEvent( TopToolWidget *sender_top_tool_widget, const TopToolEventInfo &top_tool_event_info ) {
	auto topToolDockEventInfo = TopToolDockEventInfo( );
	topToolDockEventInfo.eventType = TopToolDockEventInfo::EventType::TopToolEvent;
	TopToolDockEventInfo::TopToolEventData topData( sender_top_tool_widget, &top_tool_event_info );
	topToolDockEventInfo.topToolEventData = &topData;

	return ToolTopToolDockEvent::triggerTopToolDockEvent( mainWindow, this, topToolDockEventInfo );
}
