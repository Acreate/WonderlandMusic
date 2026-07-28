#include "titleVerticalScrollBar.h"

#include <qcoreevent.h>
#include <QKeyEvent>
#include <QWheelEvent>
TitleVerticalScrollBar::TitleVerticalScrollBar( QWidget *parent ) : QScrollBar( parent ) {
}
void TitleVerticalScrollBar::changeEvent( QEvent *e ) {
	e->ignore( );
}
void TitleVerticalScrollBar::keyPressEvent( QKeyEvent *ev ) {
	ev->ignore( );
}
void TitleVerticalScrollBar::sliderChange( SliderChange change ) {
}
void TitleVerticalScrollBar::wheelEvent( QWheelEvent *wheel_event ) {
	wheel_event->ignore( );
}
