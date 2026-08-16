#include "musicListWidget.h"

#include <QJsonObject>
#include <QPainter>

#include <head/release_macro.h>

#include <mutex/userMutex.h>

#include "../musicCentreWidget.h"

#include "../../Item/favoriteItem/favoriteItem.h"

#include "../musicFavoriteWidget/musicFavoriteWidget.h"

#include "../musicTitleWidget/musicTitleWidget.h"

MusicListWidget::MusicListWidget( MusicCentreWidget *music_centre_widget ) : QWidget( music_centre_widget ), musicCentreWidget( music_centre_widget ) {
}
MusicListWidget::~MusicListWidget( ) {
	deleteResource( );
}
bool MusicListWidget::deleteResource( ) {
	if( userMutex == nullptr )
		return true;
	userMutex->lock( );
	currentFavoriteItem = nullptr;
	userMutex->unlock( );
	Delete_Resource_App_Core_Ptr( userMutex );
	Delete_Resource_App_Core_Ptr( drawBuff );
	Delete_Resource_App_Core_Ptr( itemWidthInfo );
	return true;
}
void MusicListWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );

	QPainter painter( this );
	if( currentFavoriteItem == nullptr )
		return;
	if( userMutex == nullptr )
		return;
	if( userMutex->tryLock( ) == false )
		return;
	painter.drawImage( 0, 0, *drawBuff );
	userMutex->unlock( );
	qDebug( ) << __func__;
}
bool MusicListWidget::setMusicListMenu( IMusicListMenu *music_list_menu ) {
	this->musicListMenu = music_list_menu;
	return true;
}
bool MusicListWidget::updateMusicListInfo( ) {
	if( currentFavoriteItem == nullptr )
		return false;
	if( userMutex == nullptr )
		return false;
	if( userMutex->tryLock( ) == false )
		return false;
	currentFavoriteItem->updateItemWidthInfo( *itemWidthInfo );
	*drawBuff = *currentFavoriteItem->getDrawBuff( );
	drawBuff->detach( );
	auto size = drawBuff->size( );
	userMutex->unlock( );
	resize( size );
	return true;
}

void MusicListWidget::updateItemWidthInfo( const ItemWidthInfo &item_width_info ) {
	userMutex->lock( );
	*itemWidthInfo = item_width_info;
	QSize *newSize = nullptr;
	if( currentFavoriteItem ) {
		currentFavoriteItem->updateItemWidthInfo( *itemWidthInfo );
		newSize = new QSize( currentFavoriteItem->getDrawBuff( )->size( ) );
	}
	userMutex->unlock( );
	if( newSize ) {
		resize( *newSize );
		delete newSize;
		updateMusicListInfo( );
	}
}

FavoriteItem * MusicListWidget::getCurrentFavoriteItem( ) const {
	return currentFavoriteItem;
}
void MusicListWidget::setCurrentFavoriteItem( FavoriteItem *favorite_item ) {
	currentFavoriteItem = favorite_item;

	updateMusicListInfo( );
}
IMusicListMenu * MusicListWidget::getMusicListMenu( ) const {
	return musicListMenu;
}
bool MusicListWidget::initBefore( ) {
	deleteResource( );
	userMutex = new UserMutex;
	drawBuff = new QImage;
	itemWidthInfo = new ItemWidthInfo;
	return true;
}
bool MusicListWidget::init( ) {
	return true;
}
bool MusicListWidget::initAfter( ) {
	return true;
}
bool MusicListWidget::getJsonData( QJsonObject &get_json_object ) const {
	if( currentFavoriteItem == nullptr )
		return false;
	get_json_object.insert( "currentFavoriteItem", currentFavoriteItem->getFavoriteItemName( ) );
	return true;
}
bool MusicListWidget::setJsonData( const QJsonObject &set_json_object ) {
	auto find = set_json_object.find( "currentFavoriteItem" );
	auto end = set_json_object.end( );
	if( find == end )
		return false;
	auto favoriteName = find->toString( );

	if( musicCentreWidget->getMusicFavoriteWidget( )->getNameFavoriteItem( currentFavoriteItem, favoriteName ) == false )
		return false;
	return true;
}
MusicCentreWidget * MusicListWidget::getMusicCentreWidget( ) const {
	return musicCentreWidget;
}
