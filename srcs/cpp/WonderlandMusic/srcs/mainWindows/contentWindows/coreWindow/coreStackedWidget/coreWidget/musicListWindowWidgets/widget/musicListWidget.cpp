#include "musicListWidget.h"

#include <QPainter>
MusicListWidget::MusicListWidget( QWidget *parent ) : BaseWidget( parent ) {

}
void MusicListWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );

	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::GlobalColor::black );
}
