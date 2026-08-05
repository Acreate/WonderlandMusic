#include "musicToolWidget.h"

#include <QPainter>

#include "../musicCentreWidget.h"
MusicToolWidget::MusicToolWidget( MusicCentreWidget *music_centre_widget ) : QWidget( music_centre_widget ), musicCentreWidget( music_centre_widget ) {
}
MusicToolWidget::~MusicToolWidget( ) {
	deleteResource( );
}
bool MusicToolWidget::deleteResource( ) {
	return true;
}
void MusicToolWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );
	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::GlobalColor::red );
}
bool MusicToolWidget::initBefore( ) {
	return true;
}
bool MusicToolWidget::init( ) {
	return true;
}
bool MusicToolWidget::initAfter( ) {
	setFixedHeight( 50 );
	return true;
}
int MusicToolWidget::getSuggestHeight( ) const {
	return height( );
}
