#include "playerDockWidget.h"

#include <QPainter>

#include "../contentWindow.h"
PlayerDockWidget::PlayerDockWidget( ContentWindow *parent ) : QDockWidget( parent ), contentWindow( parent ) {

}
void PlayerDockWidget::paintEvent( QPaintEvent *event ) {
	QDockWidget::paintEvent( event );

	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::GlobalColor::white );
}
