#include "musicVectorInfoWidget.h"

#include <QPainter>
void MusicVectorInfoWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::GlobalColor::yellow );
}
