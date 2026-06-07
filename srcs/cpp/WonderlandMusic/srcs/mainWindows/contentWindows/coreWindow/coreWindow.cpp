#include "coreWindow.h"

#include <QPainter>

#include "../contentWindow.h"

#include "coreStackedWidget/coreStackedWidget.h"
CoreWindow::CoreWindow( ContentWindow *parent ) : QMainWindow( parent ), contentWindow( parent ) {
	coreStackedWidget = new CoreStackedWidget( this );
	setCentralWidget( coreStackedWidget );
}
bool CoreWindow::showMusicWidget( ) {
	return coreStackedWidget->showMusicWidget( );
}
bool CoreWindow::showSettingWidget( ) {
	return coreStackedWidget->showSettingWidget( );
}

