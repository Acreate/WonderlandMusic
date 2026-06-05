#include "musicListWindow.h"

#include <QPainter>

#include "../coreStackedWidget.h"
MusicListWindow::MusicListWindow( CoreStackedWidget *parent ) : QMainWindow( parent ), coreStackedWidget( parent ) {

}
void MusicListWindow::paintEvent( QPaintEvent *event ) {
	QMainWindow::paintEvent( event );

	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::GlobalColor::black );
}
