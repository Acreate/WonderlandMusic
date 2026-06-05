#include "appFunctionScrollArea.h"

#include "../widget/appFunctionWidget.h"
AppFunctionScrollArea::AppFunctionScrollArea( QWidget *parent ) : QScrollArea( parent ) {
	setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	setWidgetResizable( true );
	appFunctionWidget = new AppFunctionWidget;
	setWidget( appFunctionWidget );
}
