#include "musicItemWidget.h"

#include "../../component/musicWindow/interface/widget/iMusicListWidget.h"
#include "../../component/musicWindow/musicCentreWidget/musicCentreWidget.h"
MusicItemWidget::MusicItemWidget( ) {
	appendTypeInfo( this );
	hide( );
}
MusicItemWidget::~MusicItemWidget( ) {
}
bool MusicItemWidget::setMusicCentreWidget( MusicCentreWidget *music_centre_widget ) {
	musicCentreWidget = music_centre_widget;
	return true;
}
MusicCentreWidget * MusicItemWidget::getMusicCentreWidget( ) const {
	return musicCentreWidget;
}
bool MusicItemWidget::updateLayout( ) {
	return true;
}
bool MusicItemWidget::setMusicListWidget( IMusicListWidget *music_list_widget ) {
	setParent( music_list_widget->toWidget( ) );
	return true;
}
bool MusicItemWidget::bindMusicItem( IMusicItem *music_item ) {
	musicItem = music_item;
	return true;
}
IMusicItem * MusicItemWidget::getBindMusicItem( ) const {
	return musicItem;
}
