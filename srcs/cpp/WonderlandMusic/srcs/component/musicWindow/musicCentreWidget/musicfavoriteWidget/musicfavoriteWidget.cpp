#include "musicfavoriteWidget.h"

#include <QPainter>

#include "../musicCentreWidget.h"
MusicfavoriteWidget::MusicfavoriteWidget( MusicCentreWidget *music_centre_widget ) : QWidget( music_centre_widget ), musicCentreWidget( music_centre_widget ) {
}
MusicfavoriteWidget::~MusicfavoriteWidget( ) {
	deleteResource( );
}
bool MusicfavoriteWidget::deleteResource( ) {
	return true;
}
void MusicfavoriteWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );

	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::GlobalColor::darkBlue );
}
bool MusicfavoriteWidget::initBefore( ) {
	return true;
}
bool MusicfavoriteWidget::init( ) {
	return true;
}
bool MusicfavoriteWidget::initAfter( ) {
	return true;
}
int MusicfavoriteWidget::getSuggestWidth( ) const {
	return 50;
}
bool MusicfavoriteWidget::getJsonData( QJsonObject &get_json_object ) const {
	return true;
}
bool MusicfavoriteWidget::setJsonData( const QJsonObject &set_json_object ) {
	return true;
}
