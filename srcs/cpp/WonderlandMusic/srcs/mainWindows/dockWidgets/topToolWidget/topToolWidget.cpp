#include "topToolWidget.h"

#include "../topToolDockWidget.h"

#include <QHBoxLayout>
#include <QPushButton>
TopToolWidget::TopToolWidget( TopToolDockWidget *parent ) : QWidget( parent ), parent( parent ) {
	closeBtn = new QPushButton( tr( "关闭" ), this );
	minMainWindowBtn = new QPushButton( tr( "最小化" ), this );
}
void TopToolWidget::resizeEvent( QResizeEvent *event ) {
	QWidget::resizeEvent( event );
	auto rect = contentsRect( );
	int width = rect.width( ) - rect.x( );
	int moveTargetX = width - closeBtn->width( );
	closeBtn->move( moveTargetX, 0 );
	width = moveTargetX - minMainWindowBtn->width( );
	minMainWindowBtn->move( width, 0 );
	width = closeBtn->height( );
	moveTargetX = minMainWindowBtn->height( );
	if( width < moveTargetX )
		width = moveTargetX;
	setFixedHeight( width );
}
