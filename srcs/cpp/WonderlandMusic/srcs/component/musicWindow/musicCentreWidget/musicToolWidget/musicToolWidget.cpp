#include "musicToolWidget.h"

#include <QJsonObject>
#include <QPainter>

#include "../musicCentreWidget.h"

#include <head/q_json_object.h>
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
	playerVolume = 0.3f;
	setFixedHeight( 50 );
	return true;
}
int MusicToolWidget::getSuggestHeight( ) const {
	return height( );
}
bool MusicToolWidget::getJsonData( QJsonObject &get_json_object ) const {
	instaerJsonObj( get_json_object, playerVolume );
	instaerJsonObj( get_json_object, playerMusicFile );
	instaerJsonObj( get_json_object, playerDuration );
	return true;
}
bool MusicToolWidget::setJsonData( const QJsonObject &set_json_object ) {
	QJsonObject::const_iterator end;
	QJsonObject::const_iterator find;
	bool ok;
	QString string;
	end = set_json_object.end( );
	getJsonObj( set_json_object, playerVolume, find, end, ok );
	if( ok ) {
		string = find->toString( "0.3" );
		playerVolume = string.toDouble( &ok );
	}
	getJsonObj( set_json_object, playerMusicFile, find, end, ok );
	if( ok )
		playerMusicFile = find->toString( );
	getJsonObj( set_json_object, playerDuration, find, end, ok );
	if( ok ) {
		string = find->toString( "0" );
		playerVolume = string.toLongLong( &ok );
	}
	return true;
}
