#include "transparencyScrollBar.h"

#include <QPainter>
#include <qcoreevent.h>
TransparencyScrollBar::TransparencyScrollBar( QWidget *widget ) : QScrollBar( widget ) {
	setAttribute( Qt::WA_TransparentForMouseEvents, true );
	setAttribute( Qt::WA_TranslucentBackground, true );
	setAttribute( Qt::WA_NoSystemBackground, true );
	setAttribute( Qt::WA_OpaquePaintEvent, false );
	setEnabled( false );
}
TransparencyScrollBar::~TransparencyScrollBar( ) {
}
bool TransparencyScrollBar::event( QEvent *event ) {
	switch( event->type( ) ) {
		case QEvent::Type::Paint :
			event->ignore( );
			return true;
	}
	return QScrollBar::event( event );
}
