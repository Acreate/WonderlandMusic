#include "findDockWidget.h"

#include <QPainter>

#include "../mainWindows/contentWindow.h"
FindDockWidget::FindDockWidget( ContentWindow *parent ) : BaseDockWidget( parent ), contentWindow( parent ) {

}
void FindDockWidget::paintEvent( QPaintEvent *event ) {
	QDockWidget::paintEvent( event );
	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::GlobalColor::white );
}
