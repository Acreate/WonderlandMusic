#include "widgetTools.h"

#include <QMenu>
#include <QWidget>
#include <qscreen.h>

#include "../application/appInstance.h"

void WidgetTools::moveWidgetToCenterPos( const QPoint &target_pos, QWidget *move_source_widget ) {
	move_source_widget->adjustSize( );
	int width = move_source_widget->width( );
	int height = move_source_widget->height( );
	auto x = target_pos.x( ) - width / 2;
	auto y = target_pos.y( ) - height / 2;
	move_source_widget->move( x, y );
}

void WidgetTools::moveWidgetToCenterPos( const QWidget *target_widget_pos, QWidget *move_source_widget ) {
	auto targetPos = target_widget_pos->geometry( ).center( );
	WidgetTools::moveWidgetToCenterPos( targetPos, move_source_widget );
}

bool WidgetTools::getMenuSuggestionShowMenuPos( QPoint &suggestion_show_pos, const QPoint &org_pos, QMenu *calculation_menu ) {
	calculation_menu->adjustSize( );
	auto menuWidth = calculation_menu->width( );
	auto menuHeight = calculation_menu->height( );
	auto screens = AppInstance::getAppInstance( )->screens( );
	qsizetype count = screens.size( );
	auto data = screens.data( );
	qsizetype index = 0;
	for( ; index < count; index += 1 ) {
		auto geometry = data[ index ]->geometry( );
		if( geometry.contains( org_pos ) ) {
			auto screenSize = data[ index ]->size( );
			auto screenWidth = screenSize.width( );
			auto screenHeight = screenSize.height( );

			int x = org_pos.x( );
			x = screenWidth < menuWidth + x ? x - menuWidth : x;
			int y = org_pos.y( );
			y = screenHeight < menuHeight + y ? y - menuHeight : y;
			suggestion_show_pos = QPoint( x, y );
			return true;
		}
	}
	return false;
}
