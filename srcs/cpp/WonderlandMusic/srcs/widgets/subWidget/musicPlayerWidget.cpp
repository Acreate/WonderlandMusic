#include "musicPlayerWidget.h"

#include <QPainter>
void MusicPlayerWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	
	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::GlobalColor::black );
}
