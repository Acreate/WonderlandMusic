#include "musicToolWidget.h"
MusicToolWidget::MusicToolWidget( QWidget *parent ) : QWidget( parent ) {
}
MusicToolWidget::~MusicToolWidget( ) {
	deleteResource( );
}
bool MusicToolWidget::deleteResource( ) {
	return true;
}
bool MusicToolWidget::initBefore( ) {
	return true;
}
bool MusicToolWidget::init( ) {
	return true;
}
bool MusicToolWidget::initAfter( ) {
	return true;
}
