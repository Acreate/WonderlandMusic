#include "appFunctionWidget.h"

#include <QPainter>
#include <QMouseEvent>
#include <QVBoxLayout>

#include "../../../msgInfo/messageErrorOut.h"

#include "../itemWidget/appFunctionWidgetItemWidget.h"

AppFunctionWidget::AppFunctionWidget( QWidget *parent ) : QWidget( parent ) {
	QVBoxLayout *mainLayout;
	QFlags< QFlags< Qt::AlignmentFlag >::enum_type > alignment;
	AppFunctionWidgetItemWidget *appFunctionWidgetItemWidget;

	mainLayout = new QVBoxLayout( this );
	alignment = Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignTop;
	mainLayout->setAlignment( alignment );

	appFunctionWidgetItemWidget = new AppFunctionWidgetItemWidget( this, tr( "音乐" ) );
	mainLayout->addWidget( appFunctionWidgetItemWidget );

	appFunctionWidgetItemWidget = new AppFunctionWidgetItemWidget( this, tr( "设置" ) );
	mainLayout->addWidget( appFunctionWidgetItemWidget );
}

void AppFunctionWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
}
bool AppFunctionWidget::clinkItem( AppFunctionWidgetItemWidget *item, Qt::MouseButton mouse_button, const QPoint &pos ) {
	MessageErrorOut( ) << tr( "点击了 " ) << item->getItemName( );
	return false;
}
