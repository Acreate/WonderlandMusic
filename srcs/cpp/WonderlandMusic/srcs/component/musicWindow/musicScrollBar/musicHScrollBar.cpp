#include "musicHScrollBar.h"

#include <QMouseEvent>
MusicHScrollBar::MusicHScrollBar( QWidget *parent ) : QScrollBar( Qt::Horizontal, parent ) {
	setMouseTracking( true );
}
MusicHScrollBar::~MusicHScrollBar( ) {
}
void MusicHScrollBar::mouseMoveEvent( QMouseEvent *mouse_event ) {
	QScrollBar::mouseMoveEvent( mouse_event );
	mouse_event->ignore( );
}
void MusicHScrollBar::mousePressEvent( QMouseEvent *mouse_event ) {
	QScrollBar::mousePressEvent( mouse_event );
	mouse_event->ignore( );
}
void MusicHScrollBar::mouseReleaseEvent( QMouseEvent *mouse_event ) {
	QScrollBar::mouseReleaseEvent( mouse_event );
	mouse_event->ignore( );
}
