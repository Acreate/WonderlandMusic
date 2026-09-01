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
bool MusicScrollArea::containsPosInView( bool &result_is_contains_music_scroll_area, bool &result_is_contains_viewport, const QPoint &global_pos ) const {
	auto widget = viewport( );
	if( widget == nullptr )
		return false;
	auto geometry = widget->geometry( );
	auto fromGlobal = mapFromGlobal( global_pos );
	result_is_contains_music_scroll_area = contentsRect( ).contains( fromGlobal );
	fromGlobal = widget->mapFromGlobal( global_pos );
	result_is_contains_viewport = geometry.contains( fromGlobal );
	return result_is_contains_viewport || result_is_contains_music_scroll_area;
}
