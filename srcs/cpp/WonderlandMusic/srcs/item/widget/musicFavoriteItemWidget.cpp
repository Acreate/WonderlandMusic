#include "musicFavoriteItemWidget.h"

#include <component/musicWindow/musicCentreWidget/musicCentreWidget.h>
#include <QMouseEvent>
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
bool MusicFavoriteItemWidget::mousePress( const QMouseEvent &mouse_event ) const {
	auto mouseButton = mouse_event.button( );
	switch( mouseButton ) {
		case Qt::LeftButton :
			if( geometry( ).contains( mouse_event.pos( ) ) == false )
				return false;
			return true;
			break;
		default :
			return false;
	}
	return false;
}
bool MusicFavoriteItemWidget::mouseRelease( const QMouseEvent &mouse_event ) const {
	auto mouseButton = mouse_event.button( );
	switch( mouseButton ) {
		case Qt::LeftButton :
			if( geometry( ).contains( mouse_event.pos( ) ) == false )
				return false;
			return true;
			break;
		default :
			return false;
	}
	return false;
}
bool MusicFavoriteItemWidget::drawWidget( ) {
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
