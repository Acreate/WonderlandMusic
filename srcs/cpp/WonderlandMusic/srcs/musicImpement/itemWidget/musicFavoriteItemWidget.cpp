#include "musicFavoriteItemWidget.h"

#include <QLabel>

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
bool MusicFavoriteItemWidget::setMusicCentreWidget( IMusicCentreWidget *music_centre_widget ) {
	musicCentreWidget = music_centre_widget;
	return true;
}
IMusicCentreWidget * MusicFavoriteItemWidget::getMusicCentreWidget( ) const {
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
	QWidget *parent = music_favorite_widget->toWidget( );
	setParent( parent );
	musicFavoriteWidget = music_favorite_widget;
	if( parent == nullptr || musicFavoriteWidget == nullptr )
		hideItemWidget( );
	return true;
}
bool MusicFavoriteItemWidget::bindMusicFavoriteItem( IMusicFavoriteItem *music_favorite_item ) {
	musicFavoriteItem = music_favorite_item;
	return true;
}
IMusicFavoriteItem * MusicFavoriteItemWidget::getBindMusicFavoriteItem( ) const {
	return musicFavoriteItem;
}
bool MusicFavoriteItemWidget::setPos( const int &target_pos_x, const int &target_pos_y ) {
	move( target_pos_x, target_pos_y );
	return true;
}
bool MusicFavoriteItemWidget::setSize( const int &set_width, const int &set_height ) {
	resize( set_width, set_height );
	return true;
}
bool MusicFavoriteItemWidget::getPos( int &target_pos_x, int &target_pos_y ) const {
	auto point = pos( );
	target_pos_x = point.x( );
	target_pos_y = point.y( );
	return true;
}
bool MusicFavoriteItemWidget::getSize( int &result_width, int &result_height ) const {
	auto widgetSize = size( );
	result_width = widgetSize.width( );
	result_height = widgetSize.height( );
	return true;
}
bool MusicFavoriteItemWidget::showItemWidget( ) {
	if( musicFavoriteWidget == nullptr )
		return false;
	show( );

	return true;
}
bool MusicFavoriteItemWidget::hideItemWidget( ) {
	hide( );
	return true;
}
