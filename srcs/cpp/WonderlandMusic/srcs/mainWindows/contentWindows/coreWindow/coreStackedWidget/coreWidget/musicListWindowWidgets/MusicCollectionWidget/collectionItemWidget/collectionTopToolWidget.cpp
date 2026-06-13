#include "collectionTopToolWidget.h"

#include <QLabel>

#include <applications/applicationInstance.h>

#include <applications/applicationEvenTrigger.h>

CollectionTopToolWidget::CollectionTopToolWidget( QWidget *parent ) : BaseWidget( parent ) {
	setMinimumHeight( 50 );
	title = new QLabel( tr( "收藏栏" ), this );
}
CollectionTopToolWidget::~CollectionTopToolWidget( ) {
	delete title;
}
void CollectionTopToolWidget::resizeEvent( QResizeEvent *event ) {
	BaseWidget::resizeEvent( event );
	title->setGeometry( contentsRect( ) );
}
