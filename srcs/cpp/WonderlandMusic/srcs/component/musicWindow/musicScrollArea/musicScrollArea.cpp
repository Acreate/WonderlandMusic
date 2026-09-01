#include "musicScrollArea.h"

#include <QMouseEvent>
MusicScrollArea::MusicScrollArea( QWidget *parent ) : QScrollArea( parent ) {
	setWidgetResizable( true );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setMouseTracking( true );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
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
