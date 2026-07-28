#include "musicCentreWidget.h"

#include "../../../musicWindow.h"

MusicCentreWidget::MusicCentreWidget( MusicWindow *parent ) : QWidget( parent ), musicWindow( parent ) {
}
MusicCentreWidget::~MusicCentreWidget( ) {
	deleteResource( );
}
bool MusicCentreWidget::deleteResource( ) {
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
	return true;
}
void MusicCentreWidget::clearShowMusic( ) {
}
