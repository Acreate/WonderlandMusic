#include "playerInfoListWidgetScrollArea.h"

#include <QMouseEvent>
PlayerInfoListWidgetScrollArea::PlayerInfoListWidgetScrollArea( ) : QScrollArea( ) {
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
