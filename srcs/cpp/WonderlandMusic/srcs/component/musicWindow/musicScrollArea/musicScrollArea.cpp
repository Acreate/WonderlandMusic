#include "musicScrollArea.h"

#include <QMouseEvent>

#include "../musicScrollBar/musicHScrollBar.h"
#include "../musicScrollBar/musicVScrollBar.h"
MusicScrollArea::MusicScrollArea( QWidget *parent ) : QScrollArea( parent ) {
	setWidgetResizable( true );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setMouseTracking( true );
	setHorizontalScrollBar( new MusicHScrollBar( this ) );
	setVerticalScrollBar( new MusicVScrollBar( this ) );
}
void MusicScrollArea::mouseMoveEvent( QMouseEvent *mouse_event ) {
	QScrollArea::mouseMoveEvent( mouse_event );
	mouse_event->ignore( );
}
void MusicScrollArea::mousePressEvent( QMouseEvent *mouse_event ) {
	QScrollArea::mousePressEvent( mouse_event );
	mouse_event->ignore( );
}
void MusicScrollArea::mouseReleaseEvent( QMouseEvent *mouse_event ) {
	QScrollArea::mouseReleaseEvent( mouse_event );
	mouse_event->ignore( );
}

bool MusicScrollArea::event( QEvent *event ) {
	return QScrollArea::event( event );
}
