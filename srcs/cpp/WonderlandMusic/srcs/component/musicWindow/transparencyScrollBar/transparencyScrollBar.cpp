#include "transparencyScrollBar.h"

#include <QPainter>
#include <qcoreevent.h>
TransparencyScrollBar::TransparencyScrollBar( QWidget *widget ) : QScrollBar( widget ) {
	//setWindowFlags( Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint );
	setAttribute( Qt::WA_TransparentForMouseEvents, true );
	setAttribute( Qt::WA_TranslucentBackground, true );
	setAttribute( Qt::WA_NoSystemBackground, true );
	setAttribute( Qt::WA_OpaquePaintEvent, false );
	setEnabled( false );
}
TransparencyScrollBar::~TransparencyScrollBar( ) {
}
bool TransparencyScrollBar::event( QEvent *event ) {
	event->ignore( );
	QPainter *painter;
	switch( event->type( ) ) {
		case QEvent::Paint :
			painter = new QPainter( this );
			painter->fillRect( contentsRect( ), Qt::GlobalColor::transparent );
			delete painter;
			break;
		default :
			break;
	}
	return true;
}
