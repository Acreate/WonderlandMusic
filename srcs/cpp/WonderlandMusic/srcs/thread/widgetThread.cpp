#include "widgetThread.h"

#include <QWidget>

WidgetThread::WidgetThread( QWidget *bind_widget ) : QThread( bind_widget ), bindWidget( bind_widget ) {
	connect( this, &QThread::finished, [this]( ) {
		if( finishedCallFunction )
			finishedCallFunction( this, bindWidget );
	} );
}

const QWidget * WidgetThread::getBindWidget( ) const {
	return bindWidget;
}

const std::function< void( WidgetThread *, QWidget * ) > & WidgetThread::getCall( ) const {
	return runCallFunction;
}

void WidgetThread::setCall( const std::function< void( WidgetThread *, QWidget * ) > &call ) {
	this->runCallFunction = call;
}

const std::function< void( WidgetThread *, QWidget * ) > & WidgetThread::getFinishedCallFunction( ) const {
	return finishedCallFunction;
}

void WidgetThread::setFinishedCallFunction( const std::function< void( WidgetThread *, QWidget * ) > &finished_call_function ) {
	finishedCallFunction = finished_call_function;
}

void WidgetThread::run( ) {
	if( runCallFunction )
		runCallFunction( this, bindWidget );
}
