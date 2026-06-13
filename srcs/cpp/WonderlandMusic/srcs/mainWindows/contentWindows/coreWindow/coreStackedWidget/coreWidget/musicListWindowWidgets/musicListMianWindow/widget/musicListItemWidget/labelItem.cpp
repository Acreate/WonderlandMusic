#include "labelItem.h"

#include <QLabel>
#include <QPainter>
#include <qevent.h>

#include <applications/applicationInstance.h>
#include <render/render.h>
LabelItem::LabelItem( const QString &title_name, QWidget *parent ) : BaseWidget( parent ) {
	drawDecollatorWidth = 2;
	drawDecollatorInterspace = 10;
	titleName = new QLabel( title_name, this );
	titleName->move( drawDecollatorInterspace, 0 );
	auto render = ApplicationInstance::getApplicationInstance( )->getRender( );
	auto font = render->getFont( );
	titleName->setFont( font );
	titleName->adjustSize( );
	setFixedSize( drawDecollatorInterspace + titleName->width( ), titleName->height( ) );
}
QString LabelItem::getTitleName( ) const {
	return titleName->text( );
}
bool LabelItem::isContainsDecollator( const QPoint &parent_point ) const {
	int comp = parent_point.x( );
	QRect geometry = this->geometry( );
	int x = geometry.x( );
	if( comp < x || comp > drawDecollatorInterspace + x )
		return false;
	comp = parent_point.y( );
	int y = geometry.y( );
	if( comp < y || comp > height( ) )
		return false;
	return true;
}
void LabelItem::paintEvent( QPaintEvent *event ) {

	QPainter painter( this );
	int drawX = drawDecollatorInterspace - drawDecollatorWidth;
	auto pen = painter.pen( );
	painter.setPen( pen );
	drawX = drawX / 2;
	painter.drawLine( drawX, 0, drawX, height( ) );

	event->accept( );
}
void LabelItem::resizeEvent( QResizeEvent *event ) {
	auto size = event->size( );
	if( size.width( ) < drawDecollatorInterspace || size.height( ) < titleName->height( ) ) {
		event->accept( );
		return;
	}
}
