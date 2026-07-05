#include "labelWidget.h"

#include <QMouseEvent>

#include "../application/appInstance.h"
#include "../application/appUserInterfaceManage.h"

LabelWidget::LabelWidget( const QString &text, QWidget *parent, const Qt::WindowFlags &f ) : QLabel( text, parent, f ) {
	click = false;
}

LabelWidget::LabelWidget( const QString &text, QWidget *parent ) : LabelWidget( text, parent, Qt::WindowFlags( ) ) {
}

LabelWidget::LabelWidget( const QString &text ) : LabelWidget( text, nullptr, Qt::WindowFlags( ) ) {
}

LabelWidget::LabelWidget( ) : LabelWidget( "", nullptr, Qt::WindowFlags( ) ) {
}

void LabelWidget::mousePressEvent( QMouseEvent *ev ) {
	QLabel::mousePressEvent( ev );
	click = true;
}

void LabelWidget::mouseReleaseEvent( QMouseEvent *ev ) {
	QLabel::mouseReleaseEvent( ev );
	if( click == false )
		return;

	auto mouseButton = ev->button( );
	switch( mouseButton ) {
		case Qt::NoButton :
			break;
		case Qt::LeftButton :
			emit AppInstance::getAppInstance( )->getAppUserInterfaceManage( )->signal_click_favorite_Item( this );
			break;
		case Qt::RightButton :
			emit AppInstance::getAppInstance( )->getAppUserInterfaceManage( )->signal_click_favorite_Item( this );
			break;
		case Qt::MiddleButton :
			break;
	}

	click = false;
}
