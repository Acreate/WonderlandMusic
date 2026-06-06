#include "functionDockWidget.h"

#include <QPainter>

#include "../mainWindow.h"

#include "functionWidget/functionWidget.h"
FunctionDockWidget::FunctionDockWidget( MainWindow *parent ) : QDockWidget( parent ), mainWindow( parent ) {
	functionWidget = new FunctionWidget( this );
	setWidget( functionWidget );
	setContentsMargins( 0, 0, 0, 0 );
}
void FunctionDockWidget::paintEvent( QPaintEvent *event ) {
	QDockWidget::paintEvent( event );
	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::GlobalColor::darkYellow );
}
size_t FunctionDockWidget::triggerFunctionWidgetEvent( FunctionWidget *sender_function_widget, const FunctionWidgetEventInfo &function_widget_event_info ) {
	switch( function_widget_event_info.getEventType( ) ) {
		case FunctionWidgetEventInfo::EventType::None :
			break;
		case FunctionWidgetEventInfo::EventType::Show_Music :
			return FunctionDockWidgetEvent::triggerFunctionDockWidgetEvent( mainWindow, this, FunctionDockWidgetEventInfo( FunctionDockWidgetEventInfo::EventType::Show_Music ) );
		case FunctionWidgetEventInfo::EventType::Show_Setting :
			return FunctionDockWidgetEvent::triggerFunctionDockWidgetEvent( mainWindow, this, FunctionDockWidgetEventInfo( FunctionDockWidgetEventInfo::EventType::Show_Setting ) );
	}
	return 0;
}
