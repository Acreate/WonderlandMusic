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
