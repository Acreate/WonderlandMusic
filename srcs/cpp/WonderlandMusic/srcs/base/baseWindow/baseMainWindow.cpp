#include "baseMainWindow.h"

BaseMainWindow::BaseMainWindow( QWidget *parent ) : QMainWindow( parent ), BaseClass( ) {
	setContextMenuPolicy( Qt::NoContextMenu );
}
BaseMainWindow::BaseMainWindow( ) : BaseMainWindow( nullptr ) {
}
