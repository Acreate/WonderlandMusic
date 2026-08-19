#include "musicWidgetSizeInfo.h"
MusicWidgetSizeInfo::MusicWidgetSizeInfo( ) {
	appendTypeInfo( this );
}
MusicWidgetSizeInfo::~MusicWidgetSizeInfo( ) {
}
bool MusicWidgetSizeInfo::setMusicCentreWidget( MusicCentreWidget *music_centre_widget ) {
	return false;
}
int MusicWidgetSizeInfo::getFavoriteWidth( ) const {
	return 0;
}
int MusicWidgetSizeInfo::getTitleHeight( ) const {
	return 0;
}
bool MusicWidgetSizeInfo::updateMusicWidgetLayout( ) {
	return false;
}
bool MusicWidgetSizeInfo::getJsonData( QJsonObject &get_json_object ) const {
	return false;
}
bool MusicWidgetSizeInfo::setJsonData( const QJsonObject &set_json_object ) {
	return false;
}
int MusicWidgetSizeInfo::setFavoriteWidth( const int &favoriet_width ) {
	return 0;
}
int MusicWidgetSizeInfo::setTitleHeight( const int &favoriet_width ) {
	return 0;
}
