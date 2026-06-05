#include "musicPlayerWidget.h"

#include <QPainter>
#include <QMouseEvent>

void MusicPlayerWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );

	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::GlobalColor::black );
}
