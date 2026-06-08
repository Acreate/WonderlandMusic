#include "musicListWindow.h"

#include <QPainter>

#include "../coreStackedWidget.h"

#include "musicListWindowWidgets/musicListMainWidget.h"
MusicListWindow::MusicListWindow( CoreStackedWidget *parent ) : BaseMainWindow( parent ), coreStackedWidget( parent ) {
	setCentralWidget( new MusicListMainWidget( this ) );
}
