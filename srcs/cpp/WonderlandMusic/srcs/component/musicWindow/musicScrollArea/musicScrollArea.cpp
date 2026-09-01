#include "musicScrollArea.h"

#include <QMouseEvent>
MusicScrollArea::MusicScrollArea( QWidget *parent ) : QScrollArea( parent ) {
	setWidgetResizable( true );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setAttribute( Qt::WA_TransparentForMouseEvents, true );
	setMouseTracking( true );
}

bool MusicScrollArea::event( QEvent *event ) {
	switch( event->type( ) ) {
		case QEvent::MouseButtonPress :
		case QEvent::MouseButtonRelease :
		case QEvent::MouseMove :
		case QEvent::MouseButtonDblClick :
		case QEvent::Wheel : {
			event->ignore( );
			return true;
		}
		default :
			break;
	}
	return QScrollArea::event( event );
}
