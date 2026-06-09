#include "widgetTools.h"

#include <QWidget>
void WidgetTools::moveWidgetToCenterPos( const QPoint &target_pos, QWidget *move_source_widget ) {
	move_source_widget->adjustSize( );
	int width = move_source_widget->width( );
	int height = move_source_widget->height( );
	auto x = target_pos.x( ) - width / 2;
	auto y = target_pos.y( ) - height / 2;
	move_source_widget->setGeometry( x, y, width, height );
}
void WidgetTools::moveWidgetToCenterPos( const QWidget *target_widget_pos, QWidget *move_source_widget ) {
	auto targetPos = target_widget_pos->geometry( ).center( );
	WidgetTools::moveWidgetToCenterPos( targetPos, move_source_widget );
}
