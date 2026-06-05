#include "musicVectorInfoWidget.h"

#include <QPainter>
#include <QMouseEvent>

#include "item/musicVectorInfoItem.h"
void MusicVectorInfoWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::GlobalColor::yellow );
}
void MusicVectorInfoWidget::mouseReleaseEvent( QMouseEvent *event ) {
	size_t count = musicVectorInfoItems.size( );
	if( count == 0 )
		return;

	auto data = musicVectorInfoItems.data( );
	size_t index = 0;
	auto point = event->pos( ) + offset;
	for( ; index < count; ++index )
		if( data[ index ]->isHide == false && data[ index ]->rect.contains( point ) ) {
			emit clickFunctionItem( *data[ index ] );
			return;
		}
}
