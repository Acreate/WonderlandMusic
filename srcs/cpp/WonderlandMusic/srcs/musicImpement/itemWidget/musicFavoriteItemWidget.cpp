#include "musicFavoriteItemWidget.h"

#include <component/musicWindow/musicCentreWidget/musicCentreWidget.h>
#include <QMouseEvent>

#include "../../component/musicWindow/interface/widget/iMusicFavoriteWidget.h"
MusicFavoriteItemWidget::MusicFavoriteItemWidget( ) {
	appendTypeInfo( this );
	hide( );
}
MusicFavoriteItemWidget::~MusicFavoriteItemWidget( ) {
}
bool MusicFavoriteItemWidget::setMusicCentreWidget( MusicCentreWidget *music_centre_widget ) {
	if( music_centre_widget == nullptr )
		hide( );
	setParent( music_centre_widget );
	musicCentreWidget = music_centre_widget;
	return true;
}
MusicCentreWidget * MusicFavoriteItemWidget::getMusicCentreWidget( ) const {
	return musicCentreWidget;
}
bool MusicFavoriteItemWidget::updateLayout( ) {
	repaint( );
	return true;
}
bool MusicFavoriteItemWidget::setBindMusicFavoriteItem( IMusicFavoriteItem *music_favorite_item ) {
	musicFavoriteItem = music_favorite_item;
	return true;
}
IMusicFavoriteItem * MusicFavoriteItemWidget::getBindMusicFavoriteItem( ) const {
	return musicFavoriteItem;
}
bool MusicFavoriteItemWidget::setMusicFavoriteWidget( IMusicFavoriteWidget *music_favorite_widget ) {
	musicFavoriteWidget = music_favorite_widget;
	QWidget *widget = nullptr;
	if( music_favorite_widget == nullptr )
		hide( );
	else {
		widget = music_favorite_widget->toWidget( );
		if( widget == nullptr )
			hide( );
	}
	setParent( widget );
	return false;
}
QImage * MusicFavoriteItemWidget::getDrawBuff( ) {
	return nullptr;
}
IMusicFavoriteWidget * MusicFavoriteItemWidget::getMusicFavoriteWidget( ) const {
	return musicFavoriteWidget;
}
