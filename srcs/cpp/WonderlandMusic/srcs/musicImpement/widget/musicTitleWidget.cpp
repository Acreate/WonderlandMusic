#include "musicTitleWidget.h"

#include <component/musicWindow/musicCentreWidget/musicCentreWidget.h>

MusicTitleWidget::MusicTitleWidget( ) {
	appendTypeInfo( this );
}
MusicTitleWidget::~MusicTitleWidget( ) {
	deleteResource( );
}
bool MusicTitleWidget::getJsonData( QJsonObject &get_json_object ) const {
	return true;
}
bool MusicTitleWidget::setJsonData( const QJsonObject &set_json_object ) {
	return true;
}
bool MusicTitleWidget::setMusicCentreWidget( MusicCentreWidget *music_centre_widget ) {
	musicCentreWidget = music_centre_widget;
	return true;
}
bool MusicTitleWidget::deleteResource( ) {
	auto musicCentreWidget = getMusicCentreWidget( );
	if( musicCentreWidget )
		musicCentreWidget->removeMusicTitleWidget( this );
	return true;
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
QWidget * MusicTitleWidget::toWidget( ) {
	return this;
}
MusicCentreWidget * MusicTitleWidget::getMusicCentreWidget( ) const {
	return musicCentreWidget;
}
bool MusicTitleWidget::setIMusicItemWidthInfo( IMusicItemWidthInfo *music_item_width_info ) {
	musicItemWidthInfo = music_item_width_info;
	return true;
}
IMusicItemWidthInfo * MusicTitleWidget::getIMusicItemWidthInfo( ) const {
	return musicItemWidthInfo;
}
bool MusicTitleWidget::autoLayout( ) {
	return true;
}
