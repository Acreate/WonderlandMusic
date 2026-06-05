#include "musicPlayerButtonWidget.h"

#include <QPainter>
void MusicPlayerButtonWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::GlobalColor::darkCyan );
}
