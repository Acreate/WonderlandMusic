#include "musicTitleWidget.h"

#include "MusicTitleWidthInfo.h"

#include "../../../../../head/release_macro.h"
MusicTitleWidget::MusicTitleWidget( QWidget *parent ) : QWidget( parent ) {
}
MusicTitleWidget::~MusicTitleWidget( ) {
	deleteResource( );
}
bool MusicTitleWidget::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( musicTitleWidthInfo );
	return true;
}
bool MusicTitleWidget::initBefore( ) {
	deleteResource( );
	musicTitleWidthInfo = new MusicTitleWidthInfo;
	return true;
}
bool MusicTitleWidget::init( ) {
	return true;
}
bool MusicTitleWidget::initAfter( ) {
	return true;
}
void MusicTitleWidget::setMusicTitleWidthInfo( MusicTitleWidthInfo &music_title_width_info ) {
	*musicTitleWidthInfo = music_title_width_info;
	repaint( );
}
MusicTitleWidthInfo MusicTitleWidget::getMusicTitleWidthInfo( ) const {
	return *musicTitleWidthInfo;
}
