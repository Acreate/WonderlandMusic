#include "coreWindow.h"

#include <QPainter>

#include "../contentWindow.h"
CoreWindow::CoreWindow( ContentWindow *parent ) : QMainWindow( parent ), contentWindow( parent ) {

}
void CoreWindow::paintEvent( QPaintEvent *event ) {
	QMainWindow::paintEvent( event );
	QPainter painter( this );
	painter.fillRect( contentsRect( ), "#9932CC" );
}
