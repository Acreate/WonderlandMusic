#include "musicListWidget.h"

#include <QPainter>
MusicListWidget::MusicListWidget( QWidget *parent ) : QWidget( parent ) {
	setMouseTracking( true );
}
void MusicListWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );

	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::GlobalColor::black );
}
