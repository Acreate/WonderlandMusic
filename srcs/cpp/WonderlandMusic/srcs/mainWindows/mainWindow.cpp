#include "mainWindow.h"

#include "../widgets/musicWidget.h"
MainWindow::MainWindow( ) {
	musicWidget = new MusicWidget( this );
	this->setCentralWidget( musicWidget );
}
MainWindow::~MainWindow( ) {

}
void MainWindow::suggestGeometry( int move_to_x, int move_to_y, int reset_size_width, int reset_size_height ) {
	move( move_to_x, move_to_y );
	if( reset_size_width > 0 && reset_size_height > 0 )
		resize( reset_size_width, reset_size_height );
}
void MainWindow::getSuggestGeometry( int &move_to_x, int &move_to_y, int &reset_size_width, int &reset_size_height ) const {
	reset_size_width = this->width( );
	reset_size_height = this->height( );
	move_to_x = this->x( );
	move_to_y = this->y( );
}
