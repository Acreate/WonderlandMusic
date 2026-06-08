#include "baseMainWindow.h"

#include <source_location>
BaseMainWindow::BaseMainWindow( QWidget *parent ) : QMainWindow( parent ), BaseClass( ) {
	setContextMenuPolicy( Qt::NoContextMenu );
}
