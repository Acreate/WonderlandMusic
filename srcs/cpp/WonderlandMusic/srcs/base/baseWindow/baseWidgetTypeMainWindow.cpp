#include "baseWidgetTypeMainWindow.h"
BaseWidgetTypeMainWindow::BaseWidgetTypeMainWindow( QWidget *parent ) : BaseMainWindow( parent ) {
	setWindowFlags( Qt::WindowType::Widget );
}
BaseWidgetTypeMainWindow::BaseWidgetTypeMainWindow( ) : BaseWidgetTypeMainWindow( nullptr ) { }
