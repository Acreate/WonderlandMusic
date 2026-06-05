#include "appFunctionWidget.h"

#include <QPainter>
void AppFunctionWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );

	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::GlobalColor::green );
}
