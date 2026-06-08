#include "collectionItemWidget.h"

#include <QLabel>

#include "../../../../../../../../applications/applicationEvenTrigger.h"
#include "../../../../../../../../applications/applicationInstance.h"
CollectionItemWidget::CollectionItemWidget( QWidget *parent ) : BaseWidget( parent ) {
	itemTitleLable = new QLabel( tr( "默认" ), this );
}
QString CollectionItemWidget::getTitleName( ) const {
	return itemTitleLable->text( );
}
void CollectionItemWidget::setTitleName( const QString &new_title_name ) const {
	itemTitleLable->setText( new_title_name );
}
void CollectionItemWidget::resizeEvent( QResizeEvent *event ) {
	BaseWidget::resizeEvent( event );
	auto rect = contentsRect( );
	itemTitleLable->setGeometry( rect );
}
void CollectionItemWidget::mousePressEvent( QMouseEvent *event ) {
	BaseWidget::mousePressEvent( event );
	auto applicationInstance = ApplicationInstance::getApplicationInstance( );
	auto applicationEvenTrigger = applicationInstance->getApplicationEvenTrigger( );
	CollectionItemWidgetEvent::triggerCollectionItemWidgetEvent( applicationEvenTrigger, this, CollectionItemWidgetEventInfo( CollectionItemWidgetEventInfo::EventType::Mouse_Press_Event ) );
}
void CollectionItemWidget::mouseReleaseEvent( QMouseEvent *event ) {
	BaseWidget::mouseReleaseEvent( event );
	auto applicationInstance = ApplicationInstance::getApplicationInstance( );
	auto applicationEvenTrigger = applicationInstance->getApplicationEvenTrigger( );
	CollectionItemWidgetEvent::triggerCollectionItemWidgetEvent( applicationEvenTrigger, this, CollectionItemWidgetEventInfo( CollectionItemWidgetEventInfo::EventType::Mouse_Release_Event ) );
}
