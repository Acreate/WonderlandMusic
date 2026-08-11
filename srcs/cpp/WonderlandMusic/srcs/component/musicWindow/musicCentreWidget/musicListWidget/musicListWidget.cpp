#include "musicListWidget.h"

#include <QJsonObject>
#include <QPainter>

#include <head/release_macro.h>

#include <mutex/userMutex.h>

#include "../musicCentreWidget.h"

#include "../../../../head/defininition_get_json_key.h"
#include "../../../../head/q_json_object.h"

#include "../../Item/favoriteItem/favoriteItem.h"

#include "../musicFavoriteWidget/musicFavoriteWidget.h"

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
	return true;
}
void MusicListWidget::paintEvent( QPaintEvent *event ) {
	QWidget::paintEvent( event );

	QPainter painter( this );
	painter.fillRect( contentsRect( ), Qt::GlobalColor::darkGreen );

	if( currentFavoriteItem == nullptr )
		return;
	if( userMutex == nullptr )
		return;
	if( userMutex->tryLock( ) == false )
		return;
	painter.drawImage( 0, 0, *currentFavoriteItem->getDrawBuff( ) );
	userMutex->unlock( );
}
bool MusicListWidget::setMusicListMenu( IMusicListMenu *music_list_menu ) {
	this->musicListMenu = music_list_menu;
	return true;
}

void MusicListWidget::updateItemWidthInfo( MusicTitleWidget *music_title_widget, int interval_width, int separator_width, int music_code_width, int music_name_width, int music_singer_name_width, int music_duration_time_width ) {
	userMutex->lock( );
	QSize *newSize = nullptr;
	if( currentFavoriteItem ) {
		currentFavoriteItem->updateItemWidthInfo( music_title_widget, interval_width, separator_width, music_code_width, music_name_width, music_singer_name_width, music_duration_time_width );
		newSize = new QSize( currentFavoriteItem->getDrawBuff( )->size( ) );
	}
	userMutex->unlock( );
	if( newSize ) {
		resize( *newSize );
		delete newSize;
		repaint( );
	}
}

FavoriteItem * MusicListWidget::getCurrentFavoriteItem( ) const {
	return currentFavoriteItem;
}
void MusicListWidget::setCurrentFavoriteItem( FavoriteItem *favorite_item ) {
	currentFavoriteItem = favorite_item;
	repaint( );
}
IMusicListMenu * MusicListWidget::getMusicListMenu( ) const {
	return musicListMenu;
}
bool MusicListWidget::initBefore( ) {
	deleteResource( );
	userMutex = new UserMutex;
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
