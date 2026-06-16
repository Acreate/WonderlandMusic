#include "highlightBackground.h"

#include <QPainter>
#include <QWidget>
#include <qcoreevent.h>
HighlightBackground::HighlightBackground( QWidget *bind_widget ) : WidgetEffect( bind_widget ) {
}
bool HighlightBackground::eventFilter( QObject *watched, QEvent *event ) {

	bool eventFilter = WidgetEffect::eventFilter( watched, event );
	return eventFilter;
}
bool HighlightBackground::renderEffect( ) {
	QPainter painter;
	painter.begin( bindWidget );
	painter.fillRect( widgetRect, "#439db0" );
	return true;
}
