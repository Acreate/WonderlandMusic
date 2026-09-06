#include "playerInfoListWidgetScrollArea.h"

#include <QMouseEvent>

#include "../playWindow.h"
PlayerInfoListWidgetScrollArea::PlayerInfoListWidgetScrollArea( PlayWindow *play_window ) : QScrollArea( play_window ) {
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	setWidgetResizable( true );
	setMouseTracking( true );
}
PlayerInfoListWidgetScrollArea::~PlayerInfoListWidgetScrollArea( ) {
}
void PlayerInfoListWidgetScrollArea::mouseDoubleClickEvent( QMouseEvent *mouse_event ) {
	mouse_event->ignore( );
}
void PlayerInfoListWidgetScrollArea::mouseMoveEvent( QMouseEvent *mouse_event ) {
	mouse_event->ignore( );
}
void PlayerInfoListWidgetScrollArea::mousePressEvent( QMouseEvent *mouse_event ) {
	mouse_event->ignore( );
}
void PlayerInfoListWidgetScrollArea::mouseReleaseEvent( QMouseEvent *mouse_event ) {
	mouse_event->ignore( );
}
