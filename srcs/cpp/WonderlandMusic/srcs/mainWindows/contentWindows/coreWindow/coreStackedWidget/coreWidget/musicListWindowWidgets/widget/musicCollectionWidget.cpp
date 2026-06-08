#include "musicCollectionWidget.h"

#include <QPainter>

#include "collectionItemWidget/collectionItemWidget.h"
#include "collectionItemWidget/collectionTopToolWidget.h"
MusicCollectionWidget::MusicCollectionWidget( QWidget *parent ) : BaseWidget( parent ) {
	this->collectionTopToolWidget = new CollectionTopToolWidget( this );
	this->collectionTopToolWidget->move( 0, 0 );
}
MusicCollectionWidget::~MusicCollectionWidget( ) {
	delete collectionTopToolWidget;
	size_t count = collectionItemWidgets.size( );
	if( count ) {
		auto data = collectionItemWidgets.data( );
		size_t index = 0;
		for( ; index < count; ++index )
			delete data[ index ];
		collectionItemWidgets.clear( );
	}
}
void MusicCollectionWidget::resizeEvent( QResizeEvent *event ) {
	BaseWidget::resizeEvent( event );
	auto rect = contentsRect( );
	collectionTopToolWidget->setFixedWidth( rect.width( ) - rect.x( ) );
}
