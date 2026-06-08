#include "collectionTopToolWidget.h"

#include <QLabel>

#include <applications/applicationInstance.h>

#include <applications/applicationEvenTrigger.h>

CollectionTopToolWidget::CollectionTopToolWidget( QWidget *parent ) : BaseWidget( parent ) {
	setMinimumHeight( 50 );
	title = new QLabel( tr( "收藏栏" ), this );
}
void CollectionTopToolWidget::resizeEvent( QResizeEvent *event ) {
	BaseWidget::resizeEvent( event );
	title->setGeometry( contentsRect( ) );
}
void CollectionTopToolWidget::mousePressEvent( QMouseEvent *event ) {
	BaseWidget::mousePressEvent( event );

	auto applicationInstance = ApplicationInstance::getApplicationInstance( );
	auto applicationEvenTrigger = applicationInstance->getApplicationEvenTrigger( );
	CollectionTopToolWidgetEvent::triggerCollectionTopToolWidgetEvent( applicationEvenTrigger, this, CollectionTopToolWidgetEventInfo( CollectionTopToolWidgetEventInfo::EventType::Mouse_Press_Event ) );
}
void CollectionTopToolWidget::mouseReleaseEvent( QMouseEvent *event ) {
	BaseWidget::mouseReleaseEvent( event );

	auto applicationInstance = ApplicationInstance::getApplicationInstance( );
	auto applicationEvenTrigger = applicationInstance->getApplicationEvenTrigger( );
	CollectionTopToolWidgetEvent::triggerCollectionTopToolWidgetEvent( applicationEvenTrigger, this, CollectionTopToolWidgetEventInfo( CollectionTopToolWidgetEventInfo::EventType::Mouse_Release_Event ) );
}
