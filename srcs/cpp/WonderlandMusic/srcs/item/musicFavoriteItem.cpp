#include "musicFavoriteItem.h"

bool MusicFavoriteItem::setMusicCentreWidget( MusicCentreWidget *music_centre_widget ) {
	return true;
}
bool MusicFavoriteItem::setDrawBuff( QImage &image ) {
	return true;
}
bool MusicFavoriteItem::getName( QString &result_name ) const {
	return true;
}
bool MusicFavoriteItem::addMusicItem( IMusicItem *music_item ) {
	return true;
}
bool MusicFavoriteItem::removeMusicItem( IMusicItem *music_item ) {
	return true;
}
bool MusicFavoriteItem::clear( ) {
	return true;
}
bool MusicFavoriteItem::getDrawBuff( QImage &result_buff ) const {
	return true;
}
bool MusicFavoriteItem::update( ) {
	return true;
}
bool MusicFavoriteItem::fromIndexGetMusicItem( IMusicItem *&result_music_item_vector, const size_t &result_count ) {
	return true;
}
bool MusicFavoriteItem::fromMusicItemGetIndex( size_t &result_index, const IMusicItem *music_item ) {
	return true;
}
bool MusicFavoriteItem::fromNameGetFirstMusicItem( IMusicItem *&result_music_item, const QString &name ) {
	return true;
}
bool MusicFavoriteItem::fromFileBaseNameGetFirstMusicItem( IMusicItem *&result_music_item, const QString &file_base_name ) {
	return true;
}
bool MusicFavoriteItem::fromFileAbsPathGetFirstMusicItem( IMusicItem *&result_music_item, const QString &path ) {
	return true;
}
bool MusicFavoriteItem::fromSingerGetFirstMusicItem( IMusicItem *&result_music_item, const QString &singer ) {
	return true;
}
MusicFavoriteItem::MusicFavoriteItem( ) {
	appendTypeInfo( this );
}
MusicFavoriteItem::~MusicFavoriteItem( ) {
}
