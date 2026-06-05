#include "findDockWidget.h"

#include <QPainter>

#include "../contentWindow.h"
FindDockWidget::FindDockWidget( ContentWindow *parent ) : QDockWidget( parent ), contentWindow( parent ) {

}
void FindDockWidget::paintEvent( QPaintEvent *event ) {
	QDockWidget::paintEvent( event );
	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::GlobalColor::white );
}
