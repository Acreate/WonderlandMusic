#include "appFunctionWidgetItemWidget.h"
#include <QMouseEvent>
#include <QPainter>

#include "../../../applications/applicationInstance.h"

#include "../../../render/render.h"

#include "../widget/appFunctionWidget.h"
AppFunctionWidgetItemWidget::AppFunctionWidgetItemWidget( AppFunctionWidget *parent, const QString &item_name ) : QWidget( parent ), parent( parent ) {
	setItemName( item_name );
}
AppFunctionWidgetItemWidget::~AppFunctionWidgetItemWidget( ) {

}
void AppFunctionWidgetItemWidget::setItemName( const QString &item_name ) {
	itemName = item_name;
	auto render = ApplicationInstance::getInstance( )->getRender( );
	renderItem.fill( 0 );
	render->renderTextImage( renderItem, itemName );
	setFixedSize( renderItem.size( ) );
	repaint( );
}
void AppFunctionWidgetItemWidget::paintEvent( QPaintEvent *event ) {
	QPainter painter( this );
	painter.drawImage( 0, 0, renderItem );
}
void AppFunctionWidgetItemWidget::mouseReleaseEvent( QMouseEvent *event ) {
	Qt::MouseButton mouseButton = event->button( );
	AppFunctionWidgetClickEvent::clinkItem( parent, this, mouseButton, event->pos( ) );
}
