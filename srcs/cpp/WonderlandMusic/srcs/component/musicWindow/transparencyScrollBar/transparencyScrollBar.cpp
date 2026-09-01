#include "transparencyScrollBar.h"

#include <QMouseEvent>
#include <qcoreevent.h>
TransparencyScrollBar::TransparencyScrollBar( QWidget *widget ) : QScrollBar( widget ) {
	setAttribute( Qt::WA_TransparentForMouseEvents, true );
	setAttribute( Qt::WA_TranslucentBackground, true );
	setAttribute( Qt::WA_NoSystemBackground, true );
	setAttribute( Qt::WA_OpaquePaintEvent, false );
	setEnabled( false );
	setMouseTracking( true );
}
TransparencyScrollBar::~TransparencyScrollBar( ) {
}
void TransparencyScrollBar::mouseMoveEvent( QMouseEvent *mouse_event ) {
	QScrollBar::mouseMoveEvent( mouse_event );
	mouse_event->ignore( );
}
void TransparencyScrollBar::mousePressEvent( QMouseEvent *mouse_event ) {
	QScrollBar::mousePressEvent( mouse_event );
	mouse_event->ignore( );
}
void TransparencyScrollBar::mouseReleaseEvent( QMouseEvent *mouse_event ) {
	QScrollBar::mouseReleaseEvent( mouse_event );
	mouse_event->ignore( );
}
bool TransparencyScrollBar::event( QEvent *event ) {
	switch( event->type( ) ) {
		case QEvent::Paint : {
			event->accept( );
			return true;
		}
		default :
			break;
	}
	return QScrollBar::event( event );
}
