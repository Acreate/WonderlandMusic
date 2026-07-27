#include "musicCentreWidget.h"

#include "../musicWindow.h"
MusicCentreWidget::MusicCentreWidget( MusicWindow *parent ) : QWidget( parent ), musicWindow( parent ) {
}
MusicCentreWidget::~MusicCentreWidget( ) {
	deleteResource( );
}
bool MusicCentreWidget::deleteResource( ) {
	if( musicWindow->centralWidget( ) == this )
		musicWindow->takeCentralWidget( );
	return true;
}
bool MusicCentreWidget::initBefore( ) {
	deleteResource( );
	return true;
}
bool MusicCentreWidget::init( ) {
	return true;
}
bool MusicCentreWidget::initAfter( ) {
	musicWindow->setCentralWidget( this );
	return true;
}
