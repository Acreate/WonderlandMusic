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
bool MusicFavoriteItemWidget::setMusicFavoriteWidget( IMusicFavoriteWidget *music_favorite_widget ) {
	setParent( music_favorite_widget->toWidget( ) );
	return true;
}
bool MusicFavoriteItemWidget::bindMusicFavoriteItem( IMusicFavoriteItem *music_favorite_item ) {
	musicFavoriteItem = music_favorite_item;
	return true;
}
IMusicFavoriteItem * MusicFavoriteItemWidget::getBindMusicFavoriteItem( ) const {
	return musicFavoriteItem;
}
