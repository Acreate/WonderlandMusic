#include "highlightBorder.h"

#include <QPainter>
#include <QWidget>
#include <qcoreevent.h>
HighlightBorder::HighlightBorder( QWidget *bind_widget ) : WidgetEffect( bind_widget ) {
	penWdith = 4;
	pen = new QPen;
	pen->setWidth( penWdith );
}
bool HighlightBorder::eventFilter( QObject *watched, QEvent *event ) {

	bool eventFilter = WidgetEffect::eventFilter( watched, event );
	switch( event->type( ) ) {
		case QEvent::Resize :
			drawWidth = widgetRect.width( );
			drawHeight = widgetRect.height( );
			drawY = drawX = penWdith / 2;
			drawWidth -= penWdith;
			drawHeight -= penWdith;
			break;
	}
	return eventFilter;
}
bool HighlightBorder::renderEffect( ) {
	QPainter painter;
	painter.begin( bindWidget );
	painter.setPen( *pen );
	painter.drawRect( drawX, drawY, drawWidth, drawHeight );
	return true;
}
HighlightBorder::~HighlightBorder( ) {
	delete pen;
	pen = nullptr;
}
