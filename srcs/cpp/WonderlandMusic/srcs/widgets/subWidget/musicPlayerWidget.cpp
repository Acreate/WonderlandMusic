#include "musicPlayerWidget.h"

#include <QPainter>
#include <QMouseEvent>

#include "item/musicPlayerItem.h"
void MusicPlayerWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );

	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::GlobalColor::black );
}
void MusicPlayerWidget::mouseReleaseEvent( QMouseEvent *event ) {
	size_t count = musicPlayerItems.size( );
	if( count == 0 )
		return;

	auto data = musicPlayerItems.data( );
	size_t index = 0;
	auto point = event->pos( ) + offset;
	for( ; index < count; ++index )
		if( data[ index ]->isHide == false && data[ index ]->rect.contains( point ) ) {
			emit clickFunctionItem( *data[ index ] );
			return;
		}
}
