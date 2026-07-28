#include "musicTitleWidget.h"
MusicTitleWidget::MusicTitleWidget( QWidget *parent ) : QWidget( parent ) {
}
MusicTitleWidget::~MusicTitleWidget( ) {
	deleteResource( );
}
bool MusicTitleWidget::deleteResource( ) {
	return true;
}
bool MusicTitleWidget::initBefore( ) {
	return true;
}
bool MusicTitleWidget::init( ) {
	return true;
}
bool MusicTitleWidget::initAfter( ) {
	return true;
}
