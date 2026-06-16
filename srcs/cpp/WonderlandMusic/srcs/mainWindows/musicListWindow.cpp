#include "musicListWindow.h"

#include <QPainter>

#include "../stackedWidgets/coreStackedWidget.h"

#include "../widgets/musicListMainWidget.h"

MusicListWindow::MusicListWindow( CoreStackedWidget *parent ) : BaseMainWindow( parent ), coreStackedWidget( parent ) {
	
	setCentralWidget( new MusicListMainWidget( this ) );
}
