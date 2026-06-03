#include "mainWindow.h"

#include "../widgets/musicWidget.h"
MainWindow::MainWindow( ) {
	musicWidget = new MusicWidget( this );
	this->setCentralWidget( musicWidget );
}
MainWindow::~MainWindow( ) {

}
