#include "baseMainWindow.h"
BaseMainWindow::BaseMainWindow( QWidget *parent ) : QMainWindow( parent ) {
	//setMouseTracking( true );
	setContextMenuPolicy( Qt::NoContextMenu );
}
