#include "functionDockWidget.h"

#include <QPainter>

#include "../mainWindow.h"
FunctionDockWidget::FunctionDockWidget( MainWindow *parent ) : QDockWidget( parent ), mainWindow( parent ) {

}
void FunctionDockWidget::paintEvent( QPaintEvent *event ) {
	QDockWidget::paintEvent( event );
	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::GlobalColor::darkYellow );
}
