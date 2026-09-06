#include "playerControlWidgetScrollArea.h"

#include <QMouseEvent>

#include "../playWindow.h"
PlayerControlWidgetScrollArea::PlayerControlWidgetScrollArea( PlayWindow *play_window ) : QScrollArea( play_window ) {
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	setWidgetResizable( true );
	setMouseTracking( true );
}
PlayerControlWidgetScrollArea::~PlayerControlWidgetScrollArea( ) {
}
void PlayerControlWidgetScrollArea::mouseDoubleClickEvent( QMouseEvent *mouse_event ) {
	mouse_event->ignore( );
}
void PlayerControlWidgetScrollArea::mouseMoveEvent( QMouseEvent *mouse_event ) {
	mouse_event->ignore( );
}
void PlayerControlWidgetScrollArea::mousePressEvent( QMouseEvent *mouse_event ) {
	mouse_event->ignore( );
}
void PlayerControlWidgetScrollArea::mouseReleaseEvent( QMouseEvent *mouse_event ) {
	mouse_event->ignore( );
}
