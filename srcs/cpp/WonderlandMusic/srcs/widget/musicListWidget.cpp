#include "musicListWidget.h"
MusicListWidget::MusicListWidget( ) {
	appendTypeInfo( this );
}
MusicListWidget::~MusicListWidget( ) {
	deleteLater( );
}
bool MusicListWidget::getJsonData( QJsonObject &get_json_object ) const {
	return false;
}
bool MusicListWidget::setJsonData( const QJsonObject &set_json_object ) {
	return false;
}
bool MusicListWidget::setMusicCentreWidget( MusicCentreWidget *music_centre_widget ) {
	return false;
}
bool MusicListWidget::deleteResource( ) {
	return false;
}
bool MusicListWidget::initBefore( ) {
	return false;
}
bool MusicListWidget::init( ) {
	return false;
}
bool MusicListWidget::initAfter( ) {
	return false;
}
QWidget * MusicListWidget::toWidget( ) {
	return nullptr;
}
bool MusicListWidget::drawWidgeTarget( QWidget *widget ) {
	return false;
}
MusicCentreWidget * MusicListWidget::getMusicCentreWidget( ) const {
	return nullptr;
}
IMusicFavoriteItem * MusicListWidget::getCurrentMusicFavoriteItem( ) const {
	return nullptr;
}
bool MusicListWidget::setCurrentMusicFavoriteItem( IMusicFavoriteItem *music_favorite_item ) {
	return false;
}
bool MusicListWidget::fromYPosGetMusicItem( IMusicItem *&result_music_item, const size_t &y_pos ) {
	return false;
}
bool MusicListWidget::fromIndexGetMusicItem( IMusicItem *&result_music_item, const size_t &index ) {
	return false;
}
bool MusicListWidget::fromNameGetFirstMusicItem( IMusicItem *&result_music_item, const QString &name ) {
	return false;
}
bool MusicListWidget::fromFileBaseNameGetFirstMusicItem( IMusicItem *&result_music_item, const QString &file_base_name ) {
	return false;
}
bool MusicListWidget::fromFileAbsPathGetFirstMusicItem( IMusicItem *&result_music_item, const QString &path ) {
	return false;
}
bool MusicListWidget::fromSingerGetFirstMusicItem( IMusicItem *&result_music_item, const QString &singer ) {
	return false;
}
