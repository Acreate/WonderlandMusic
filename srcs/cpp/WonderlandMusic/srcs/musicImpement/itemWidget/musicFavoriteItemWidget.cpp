#include "musicFavoriteItemWidget.h"

#include <QLabel>

#include <component/musicWindow/musicCentreWidget/musicCentreWidget.h>
#include <QMouseEvent>

#include "../../component/musicWindow/interface/item/iMusicFavoriteItem.h"
#include "../../component/musicWindow/interface/widget/iMusicFavoriteWidget.h"
MusicFavoriteItemWidget::MusicFavoriteItemWidget( ) {
	appendTypeInfo( this );
	hide( );
	nameLabel = new QLabel;
	nameLabel->move( 0, 0 );
	nameLabel->setParent( this );
	nameLabel->setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Preferred );
}
MusicFavoriteItemWidget::~MusicFavoriteItemWidget( ) {
	delete nameLabel;
}
bool MusicFavoriteItemWidget::setMusicCentreWidget( MusicCentreWidget *music_centre_widget ) {
	musicCentreWidget = music_centre_widget;
	return true;
}
MusicCentreWidget * MusicFavoriteItemWidget::getMusicCentreWidget( ) const {
	return musicCentreWidget;
}
bool MusicFavoriteItemWidget::updateLayout( ) {
	QString showText;
	if( musicFavoriteItem->getName( showText ) == false )
		return false;
	nameLabel->setText( showText );
	nameLabel->adjustSize( );
	adjustSize( );
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
