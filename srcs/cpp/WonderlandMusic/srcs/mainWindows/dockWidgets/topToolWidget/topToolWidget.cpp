#include "topToolWidget.h"

#include "../topToolDockWidget.h"

#include <QHBoxLayout>
#include <QPushButton>
TopToolWidget::TopToolWidget( TopToolDockWidget *parent ) : QWidget( parent ), topToolDockWidget( parent ) {
	closeBtn = new QPushButton( tr( "关闭" ), this );
	minMainWindowBtn = new QPushButton( tr( "最小化" ), this );

	connect( closeBtn, &QPushButton::clicked, [this]( ) {
		TopToolEventInfo topToolEventInfo( TopToolEventInfo::Type::Close );
		TopToolEvent::triggerTopToolEvent( topToolDockWidget, this, topToolEventInfo );
	} );
	connect( minMainWindowBtn, &QPushButton::clicked, [this]( ) {
		TopToolEventInfo topToolEventInfo( TopToolEventInfo::Type::Min );
		TopToolEvent::triggerTopToolEvent( topToolDockWidget, this, topToolEventInfo );
	} );
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
