#include "labelItem.h"

#include <QLabel>
#include <QPainter>
#include <qevent.h>

#include <applications/applicationInstance.h>
#include <render/render.h>
LabelItem::~LabelItem( ) {
	delete renderTxtBuff;
}
LabelItem::LabelItem( const QString &title_name, QWidget *parent ) : BaseWidget( parent ), titleName( title_name ) {
	drawDecollatorWidth = 4;
	drawDecollatorInterspace = 50;
	auto render = ApplicationInstance::getApplicationInstance( )->getRender( );
	auto font = render->getFont( );
	renderTxtBuff = new QImage;
	render->renderTextImage( *renderTxtBuff, title_name );
	int height = renderTxtBuff->height( );
	int width = renderTxtBuff->width( ) + drawDecollatorInterspace;
	setFixedSize( width, height );
}
QString LabelItem::getTitleName( ) const {
	return titleName;
}

void LabelItem::paintEvent( QPaintEvent *event ) {

	QPainter painter( this );
	int drawX = drawDecollatorInterspace - drawDecollatorWidth;
	auto pen = painter.pen( );
	pen.setWidth( drawDecollatorWidth );
	painter.setPen( pen );
	drawX = drawX / 2;
	painter.drawLine( drawX, 0, drawX, height( ) );
	painter.drawImage( drawDecollatorInterspace, 0, *renderTxtBuff );
}
void LabelItem::resizeEvent( QResizeEvent *event ) {
	BaseWidget::resizeEvent( event );
}
