#include "musicItemWidthInfo.h"
MusicItemWidthInfo::MusicItemWidthInfo( ) {
	appendTypeInfo( this );
}
MusicItemWidthInfo::~MusicItemWidthInfo( ) {
}
bool MusicItemWidthInfo::setMusicCentreWidget( MusicCentreWidget *music_centre_widget ) {
	return false;
}
int MusicItemWidthInfo::getSuggestHeight( ) const {
	return 0;
}
int MusicItemWidthInfo::getClickWidth( ) const {
	return 0;
}
int MusicItemWidthInfo::getCalculateMinWidth( ) const {
	return 0;
}
int MusicItemWidthInfo::getIntervalWidth( ) const {
	return 0;
}
int MusicItemWidthInfo::getSeparatorWidth( ) const {
	return 0;
}
int MusicItemWidthInfo::getMusicCodeWidth( ) const {
	return 0;
}
int MusicItemWidthInfo::getMusicNameWidth( ) const {
	return 0;
}
int MusicItemWidthInfo::getMusicSingerNameWidth( ) const {
	return 0;
}
int MusicItemWidthInfo::getMusicDurationTimeWidth( ) const {
	return 0;
}
int MusicItemWidthInfo::getMinItemWidth( ) const {
	return 0;
}
bool MusicItemWidthInfo::setIMusicItemWidthInfo( const IMusicItemWidthInfo &music_item_width_info ) {
	return false;
}
bool MusicItemWidthInfo::getJsonData( QJsonObject &get_json_object ) const {
	return false;
}
bool MusicItemWidthInfo::setJsonData( const QJsonObject &set_json_object ) {
	return false;
}
bool MusicItemWidthInfo::updateInfo( ) {
	return false;
}
IMusicTitleWidget * MusicItemWidthInfo::setMusicTitleWidget( IMusicTitleWidget *music_title_widget ) {
	return nullptr;
}
IMusicTitleWidget * MusicItemWidthInfo::getMusicTitleWidget( ) {
	return nullptr;
}
