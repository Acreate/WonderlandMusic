#include "musicTitleWidget.h"

#include <QPainter>

#include "../musicCentreWidget.h"
MusicTitleWidget::MusicTitleWidget( MusicCentreWidget *music_centre_widget ) : QWidget( music_centre_widget ), musicCentreWidget( music_centre_widget ) {
}
MusicTitleWidget::~MusicTitleWidget( ) {
	deleteResource( );
}
bool MusicTitleWidget::deleteResource( ) {
	return true;
}
void MusicTitleWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );

	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::GlobalColor::darkYellow );
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
int MusicTitleWidget::getSuggestHeight( ) const {
	return 50;
}
