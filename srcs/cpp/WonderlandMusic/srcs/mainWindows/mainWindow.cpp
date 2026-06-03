#include "mainWindow.h"

#include "../widgets/musicWidget.h"
MainWindow::MainWindow( ) {
	setObjectName( tr( "仙村音乐播放器主窗口" ) );
	setWindowTitle( tr( "仙村音乐播放器" ) );
	musicWidget = new MusicWidget( this );
	this->setCentralWidget( musicWidget );
}
MainWindow::~MainWindow( ) {

}
