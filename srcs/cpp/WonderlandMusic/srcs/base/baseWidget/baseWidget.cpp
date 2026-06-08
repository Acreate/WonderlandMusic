#include "baseWidget.h"

#include <source_location>

#include "../../applications/applicationInstance.h"
BaseWidget::BaseWidget( QWidget *parent ) : QWidget( parent ), BaseClass( ) {
	//setMouseTracking( true );
	setContextMenuPolicy( Qt::NoContextMenu );

}
BaseWidget::BaseWidget( ) : QWidget( ), BaseClass( ) {
}
