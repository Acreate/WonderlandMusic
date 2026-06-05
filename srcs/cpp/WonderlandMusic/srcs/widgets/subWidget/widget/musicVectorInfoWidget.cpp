#include "musicVectorInfoWidget.h"

#include <QPainter>
#include <QMouseEvent>

void MusicVectorInfoWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::GlobalColor::yellow );
}
