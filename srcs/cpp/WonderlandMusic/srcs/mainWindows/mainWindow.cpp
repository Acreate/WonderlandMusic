#include "mainWindow.h"
#include "../widgets/musicWidget.h"

MainWindow::Translate::Translate( ) {
	appWindowObjectName = tr( "仙村音乐播放器" );
	windowTitleName = tr( "仙村音乐播放器主窗口" );
}
MainWindow::MainWindow( ) {
	setObjectName( translate.appWindowObjectName );
	setWindowTitle( translate.windowTitleName );
	musicWidget = new MusicWidget( this );
	this->setCentralWidget( musicWidget );

}
MainWindow::~MainWindow( ) {

}
