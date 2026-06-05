#include "appFunctionWidget.h"

#include <QPainter>
#include <QMouseEvent>

#include "item/appFunctionItem.h"
AppFunctionWidget::AppFunctionWidget( QWidget *parent ) : QWidget( parent ) {

}
void AppFunctionWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );

	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::GlobalColor::green );
}
void AppFunctionWidget::mouseReleaseEvent( QMouseEvent *event ) {
	size_t count = appFunctionItems.size( );
	if( count == 0 )
		return;

	auto data = appFunctionItems.data( );
	size_t index = 0;
	auto point = event->pos( ) + offset;
	for( ; index < count; ++index )
		if( data[ index ]->isHide == false && data[ index ]->rect.contains( point ) ) {
			emit clickFunctionItem( *data[ index ] );
			return;
		}
}
