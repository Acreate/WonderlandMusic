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
	return false;
}
bool MusicItemWidget::setBindMusicItem( IMusicItem *music_item ) {
	musicItem = music_item;
	return true;
}
IMusicItem * MusicItemWidget::getBindMusicItem( ) const {
	return musicItem;
}
QImage * MusicItemWidget::getDrawBuff( ) {
	return nullptr;
}
bool MusicItemWidget::setMusicListWidget( IMusicListWidget *music_list_widget ) {
	QWidget *widget = nullptr;
	musicListWidget = music_list_widget;
	if( music_list_widget == nullptr )
		hide( );
	else {
		widget = music_list_widget->toWidget( );
		if( widget == nullptr )
			hide( );
	}
	setParent( widget );
	return true;
}
IMusicListWidget * MusicItemWidget::getMusicListWidget( ) const {
	return musicListWidget;
}
