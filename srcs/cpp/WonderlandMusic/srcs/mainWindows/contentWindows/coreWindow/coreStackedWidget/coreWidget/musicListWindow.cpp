#include "musicListWindow.h"

#include <QPainter>

#include "../coreStackedWidget.h"

#include "musicListWindowWidgets/musicListMainWidget.h"
MusicListWindow::MusicListWindow( CoreStackedWidget *parent ) : QMainWindow( parent ), coreStackedWidget( parent ) {
	setMouseTracking( true );
	setCentralWidget( new MusicListMainWidget( this ) );
	//setContextMenuPolicy( Qt::NoContextMenu );
}
