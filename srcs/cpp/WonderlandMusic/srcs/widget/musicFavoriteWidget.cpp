#include "musicFavoriteWidget.h"
MusicFavoriteWidget::MusicFavoriteWidget( ) {
	appendTypeInfo( this );
}
MusicFavoriteWidget::~MusicFavoriteWidget( ) {
	deleteResource( );
}
bool MusicFavoriteWidget::getJsonData( QJsonObject &get_json_object ) const {
	return false;
}
bool MusicFavoriteWidget::setJsonData( const QJsonObject &set_json_object ) {
	return false;
}
bool MusicFavoriteWidget::setMusicCentreWidget( MusicCentreWidget *music_centre_widget ) {
	return false;
}
QWidget * MusicFavoriteWidget::toWidget( ) {
	return nullptr;
}
bool MusicFavoriteWidget::drawWidgeTarget( QWidget *widget ) {
	return false;
}
MusicCentreWidget * MusicFavoriteWidget::getMusicCentreWidget( ) const {
	return nullptr;
}
bool MusicFavoriteWidget::deleteResource( ) {
	return false;
}
bool MusicFavoriteWidget::initBefore( ) {
	return false;
}
bool MusicFavoriteWidget::init( ) {
	return false;
}
bool MusicFavoriteWidget::initAfter( ) {
	return false;
}
bool MusicFavoriteWidget::fromYPosGetMusicFavoriteItem( IMusicFavoriteItem *&result_music_favorite_item, const size_t &pos_y ) const {
	return false;
}
bool MusicFavoriteWidget::fromIndexGetMusicFavoriteItem( IMusicFavoriteItem *&result_music_favorite_item, const size_t &index ) const {
	return false;
}
bool MusicFavoriteWidget::fromNameGetMusicFavoriteItem( IMusicFavoriteItem *&result_music_favorite_item, const QString &index ) const {
	return false;
}
