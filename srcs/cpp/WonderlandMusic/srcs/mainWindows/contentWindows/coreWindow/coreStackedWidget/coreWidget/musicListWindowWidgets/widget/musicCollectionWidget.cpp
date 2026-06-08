#include "musicCollectionWidget.h"

#include <QPainter>
MusicCollectionWidget::MusicCollectionWidget( QWidget *parent ) : BaseWidget( parent ) {

}
void MusicCollectionWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );

	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::GlobalColor::darkBlue );
}
