#include "musicListWidget.h"

#include <QMouseEvent>

#include <component/musicWindow/interface/widget/iMusicCentreWidget.h>

#include "../../mutex/userMutex.h"

MusicListWidget::MusicListWidget( ) {
	appendTypeInfo( this );
}
MusicListWidget::~MusicListWidget( ) {
	deleteResource( );
}
bool MusicListWidget::getJsonData( QJsonObject &get_json_object ) const {
	return true;
}
bool MusicListWidget::setJsonData( const QJsonObject &set_json_object ) {
	return true;
}
bool MusicListWidget::setMusicCentreWidget( IMusicCentreWidget *music_centre_widget ) {
	musicCentreWidget = music_centre_widget;
	return true;
}
bool MusicListWidget::deleteResource( ) {
	if( userMutex == nullptr )
		return true;
	userMutex->lock( );
	auto musicCentreWidget = getMusicCentreWidget( );
	if( musicCentreWidget )
		musicCentreWidget->removeMusicListWidget( this );
	userMutex->unlock( );
	return true;
}
void MusicListWidget::mouseMoveEvent( QMouseEvent *event ) {
	event->ignore( );
}
void MusicListWidget::mousePressEvent( QMouseEvent *event ) {
	event->ignore( );
}
void MusicListWidget::mouseReleaseEvent( QMouseEvent *event ) {
	event->ignore( );
}
bool MusicListWidget::event( QEvent *event ) {
	return QWidget::event( event );
}
bool MusicListWidget::initBefore( ) {
	deleteResource( );
	userMutex = new UserMutex;
	setMouseTracking( true );
	return true;
}
bool MusicListWidget::init( ) {
	return true;
}
bool MusicListWidget::initAfter( ) {
	if( autoLayout( ) == false )
		return false;
	return true;
}
QWidget * MusicListWidget::toWidget( ) {
	return this;
}
IMusicCentreWidget * MusicListWidget::getMusicCentreWidget( ) const {
	return musicCentreWidget;
}
IMusicFavoriteItem * MusicListWidget::getCurrentMusicFavoriteItem( ) const {
	return nullptr;
}
bool MusicListWidget::setCurrentMusicFavoriteItem( IMusicFavoriteItem *music_favorite_item ) {
	return true;
}
bool MusicListWidget::fromYPosGetMusicItem( IMusicItem *&result_music_item, const size_t &y_pos ) {
	return true;
}
bool MusicListWidget::fromIndexGetMusicItem( IMusicItem *&result_music_item, const size_t &index ) {
	return true;
}
bool MusicListWidget::fromNameGetFirstMusicItem( IMusicItem *&result_music_item, const QString &name ) {
	return true;
}
bool MusicListWidget::fromFileBaseNameGetFirstMusicItem( IMusicItem *&result_music_item, const QString &file_base_name ) {
	return true;
}
bool MusicListWidget::fromFileAbsPathGetFirstMusicItem( IMusicItem *&result_music_item, const QString &path ) {
	return true;
}
bool MusicListWidget::fromSingerGetFirstMusicItem( IMusicItem *&result_music_item, const QString &singer ) {
	return true;
}
bool MusicListWidget::autoLayout( ) {
	return true;
}
