#include "musicPlayerButtonWidget.h"

#include <QPainter>
#include <QMouseEvent>

#include "item/musicPlayerButtonItem.h"
void MusicPlayerButtonWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::GlobalColor::darkCyan );
}
void MusicPlayerButtonWidget::mouseReleaseEvent( QMouseEvent *event ) {
	size_t count = musicPlayerButtonItems.size( );
	if( count == 0 )
		return;

	auto data = musicPlayerButtonItems.data( );
	size_t index = 0;
	auto point = event->pos( ) + offset;
	for( ; index < count; ++index )
		if( data[ index ]->isHide == false && data[ index ]->rect.contains( point ) ) {
			emit clickFunctionItem( *data[ index ] );
			return;
		}
}
