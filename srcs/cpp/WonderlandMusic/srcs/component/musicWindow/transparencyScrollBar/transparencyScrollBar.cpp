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
bool TransparencyScrollBar::event( QEvent *event ) {
	switch( event->type( ) ) {
		case QEvent::MouseButtonPress :
		case QEvent::MouseButtonRelease :
		case QEvent::MouseMove :
		case QEvent::MouseButtonDblClick :
		case QEvent::Wheel : {
			event->ignore( );
			return true;
		}
		case QEvent::Paint : {
			event->accept( );
			return true;
		}
		default :
			break;
	}
	return QScrollBar::event( event );
}
