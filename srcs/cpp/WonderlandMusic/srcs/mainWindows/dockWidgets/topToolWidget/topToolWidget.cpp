#include "topToolWidget.h"

#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPushButton>

#include "../topToolDockWidget.h"

#include <applications/applicationEvenTrigger.h>

#include <applications/applicationInstance.h>
TopToolWidget::TopToolWidget( TopToolDockWidget *parent ) : BaseWidget( parent ), topToolDockWidget( parent ) {
	closeBtn = new QPushButton( tr( "关闭" ), this );
	minMainWindowBtn = new QPushButton( tr( "最小化" ), this );

	connect( closeBtn, &QPushButton::clicked, [this]( ) {
		auto applicationInstance = ApplicationInstance::getApplicationInstance( );
		auto applicationEvenTrigger = applicationInstance->getApplicationEvenTrigger( );
		TopToolWidgetEventInfo topToolEventInfo( TopToolWidgetEventInfo::Type::Close );
		TopToolWidgetEvent::triggerTopToolWidgetEvent( applicationEvenTrigger, this, topToolEventInfo );
	} );
	connect( minMainWindowBtn, &QPushButton::clicked, [this]( ) {
		auto applicationInstance = ApplicationInstance::getApplicationInstance( );
		auto applicationEvenTrigger = applicationInstance->getApplicationEvenTrigger( );
		TopToolWidgetEventInfo topToolEventInfo( TopToolWidgetEventInfo::Type::Min );
		TopToolWidgetEvent::triggerTopToolWidgetEvent( applicationEvenTrigger, this, topToolEventInfo );
	} );
	drawWindow = false;
}
void TopToolWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
	auto rect = contentsRect( );
	int width = rect.width( ) - rect.x( );
	int moveTargetX = width - closeBtn->width( );
	closeBtn->move( moveTargetX, 0 );
	width = moveTargetX - minMainWindowBtn->width( );
	minMainWindowBtn->move( width, 0 );
	width = closeBtn->height( );
	moveTargetX = minMainWindowBtn->height( );
	if( width < moveTargetX )
		width = moveTargetX;
	setFixedHeight( width );
}
void TopToolWidget::leaveEvent( QEvent *event ) {
	QWidget::leaveEvent( event );
	drawWindow = false;
}
void TopToolWidget::mouseMoveEvent( QMouseEvent *event ) {
	QWidget::mouseMoveEvent( event );
	if( drawWindow ) {

		auto applicationInstance = ApplicationInstance::getApplicationInstance( );
		auto applicationEvenTrigger = applicationInstance->getApplicationEvenTrigger( );
		TopToolWidgetEvent::triggerTopToolWidgetEvent( applicationEvenTrigger, this, TopToolWidgetEventInfo( oldMousePos, ( newMousePos = event->pos( ), newMousePos ) ) );
	}
}
void TopToolWidget::mousePressEvent( QMouseEvent *event ) {
	QWidget::mousePressEvent( event );
	oldMousePos = event->pos( );
	drawWindow = true;
}
void TopToolWidget::mouseReleaseEvent( QMouseEvent *event ) {
	QWidget::mouseReleaseEvent( event );
	drawWindow = false;
	newMousePos = event->pos( );
}
