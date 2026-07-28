#include "musicToolWidget.h"
MusicToolWidget::MusicToolWidget( ): QWidget( ) {
}
MusicToolWidget::~MusicToolWidget( ) {
	deleteResource(  );
}
bool MusicToolWidget::deleteResource( ) {
	return false;
}
bool MusicToolWidget::initBefore( ) {
	return false;
}
bool MusicToolWidget::init( ) {
	return false;
}
bool MusicToolWidget::initAfter( ) {
	return false;
}
