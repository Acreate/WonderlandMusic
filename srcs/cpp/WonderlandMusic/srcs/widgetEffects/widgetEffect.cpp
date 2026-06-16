#include "widgetEffect.h"

#include <QWidget>
#include <qcoreevent.h>
WidgetEffect::WidgetEffect( QWidget *bind_widget ) : QObject( bind_widget ), bindWidget( bind_widget ) {
	bind_widget->installEventFilter( this );
}
bool WidgetEffect::eventFilter( QObject *watched, QEvent *event ) {
	bool eventFilter;
	if( watched == bindWidget ) {
		eventFilter = false;
		auto type = event->type( );
		switch( type ) {
			case QEvent::Resize :
				widgetRect = bindWidget->contentsRect( );
				widgetGeometry = bindWidget->geometry( );
				eventFilter = QObject::eventFilter( watched, event );
				break;
		}
		return eventFilter;
	}

	eventFilter = QObject::eventFilter( watched, event );
	return eventFilter;
}
WidgetEffect::~WidgetEffect( ) {
	bindWidget->removeEventFilter( this );
}
