#include "collectionItemWidget.h"

#include <QLabel>

CollectionItemWidget::CollectionItemWidget( QWidget *parent ) : BaseWidget( parent ) {
	itemTitleLable = new QLabel( tr( "默认" ), this );
	itemTitleLable->move( 0, 0 );
}
QString CollectionItemWidget::getTitleName( ) const {
	return itemTitleLable->text( );
}
void CollectionItemWidget::setTitleName( const QString &new_title_name ) const {
	itemTitleLable->setText( new_title_name );
}
void CollectionItemWidget::resizeEvent( QResizeEvent *event ) {
	BaseWidget::resizeEvent( event );
	auto rect = contentsRect( );
	itemTitleLable->setGeometry( rect );
}
