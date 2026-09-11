#include "musicVScrollBar.h"

#include <QMouseEvent>
MusicVScrollBar::MusicVScrollBar( QWidget *parent ) : QScrollBar( Qt::Vertical, parent ) {
	setMouseTracking( true );
}
void MusicVScrollBar::mouseMoveEvent( QMouseEvent *mouse_event ) {
	QScrollBar::mouseMoveEvent( mouse_event );
	mouse_event->ignore( );
}
void MusicVScrollBar::mousePressEvent( QMouseEvent *mouse_event ) {
	QScrollBar::mousePressEvent( mouse_event );
	mouse_event->ignore( );
}
void MusicVScrollBar::mouseReleaseEvent( QMouseEvent *mouse_event ) {
	QScrollBar::mouseReleaseEvent( mouse_event );
	mouse_event->ignore( );
}
