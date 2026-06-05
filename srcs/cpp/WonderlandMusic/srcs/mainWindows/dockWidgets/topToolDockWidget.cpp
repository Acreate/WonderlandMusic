#include "topToolDockWidget.h"

#include <QPainter>

#include "../mainWindow.h"
TopToolDockWidget::TopToolDockWidget( MainWindow *parent ) : QDockWidget( parent ), mainWindow( parent ) {

}
void TopToolDockWidget::paintEvent( QPaintEvent *event ) {
	QDockWidget::paintEvent( event );
	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::GlobalColor::darkBlue );
}
