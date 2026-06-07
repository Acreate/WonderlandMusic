#include "functionDockWidget.h"

#include <QPainter>

#include "../mainWindow.h"

#include "functionWidget/functionWidget.h"
FunctionDockWidget::FunctionDockWidget( MainWindow *parent ) : QDockWidget( parent ), mainWindow( parent ) {
	functionWidget = new FunctionWidget( this );
	setWidget( functionWidget );
	setContentsMargins( 0, 0, 0, 0 );
}
void FunctionDockWidget::paintEvent( QPaintEvent *event ) {
	QDockWidget::paintEvent( event );
	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::GlobalColor::darkYellow );
}
