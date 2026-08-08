#include "musicWindow.h"

#include <QJsonObject>

#include "../../application/translate/musicWindowTranslate.h"

#include "../../head/after_init_macro.h"
#include "../../head/before_init_macro.h"
#include "../../head/init_macro.h"
#include "../../head/release_macro.h"

#include "../../mutex/userMutex.h"
#include "../../tools/pathTools.h"

#include "Item/favoriteItem/favoriteItem.h"

#include "musicCentreWidget/musicCentreWidget.h"
#include "musicCentreWidget/musicListWidget/musicListWidget.h"

MusicWindow::MusicWindow( ) {
}
MusicWindow::~MusicWindow( ) {
	deleteResource( );
}
bool MusicWindow::deleteResource( ) {
	if( userMutex == nullptr )
		return true;
	userMutex->lock( );
	Delete_Resource_App_Core_Ptr( musicCentreWidget );
	userMutex->unlock( );
	Delete_Resource_App_Core_Ptr( userMutex );
	return true;
}
bool MusicWindow::initBefore( ) {
	deleteResource( );
	userMutex = new UserMutex;
	musicCentreWidget = new MusicCentreWidget( this );
	Before_Init_Resource_App_Core_Ptr( musicCentreWidget );
	return true;
}
bool MusicWindow::init( ) {
	if( AppTranslateTools::getMusicWindow( [this] ( MusicWindowTranslate &translate ) {
		setName( translate.getTitleName( ) );
	} ) == false )
		setName( tr( "音乐" ) );
	Init_Resource_App_Core_Ptr( musicCentreWidget );
	return true;
}
bool MusicWindow::initAfter( ) {
	After_Init_Resource_App_Core_Ptr( musicCentreWidget );
	setCentralWidget( musicCentreWidget );
	return true;
}
bool MusicWindow::getJsonData( QJsonObject &get_json_object ) const {
	return true;
}
bool MusicWindow::setJsonData( const QJsonObject &set_json_object ) {
	return true;
}
QWidget * MusicWindow::toWidget( ) {
	return this;
}
bool MusicWindow::hasItem( size_t &result_index, const MusicItem *music_item ) const {
	if( musicCentreWidget == nullptr )
		return false;
	auto musicListWidget = musicCentreWidget->getMusicListWidget( );
	if( musicListWidget == nullptr )
		return false;
	auto currentFavoriteItem = musicListWidget->getCurrentFavoriteItem( );
	if( currentFavoriteItem == nullptr )
		return false;
	return currentFavoriteItem->hasItem( result_index, music_item );
}
bool MusicWindow::addItem( MusicItem *music_item ) {
	if( musicCentreWidget == nullptr )
		return false;
	auto musicListWidget = musicCentreWidget->getMusicListWidget( );
	if( musicListWidget == nullptr )
		return false;
	auto currentFavoriteItem = musicListWidget->getCurrentFavoriteItem( );
	if( currentFavoriteItem == nullptr )
		return false;
	return currentFavoriteItem->addItem( music_item );
}
bool MusicWindow::updateItem( MusicItem *music_item ) {
	if( musicCentreWidget == nullptr )
		return false;
	auto musicListWidget = musicCentreWidget->getMusicListWidget( );
	if( musicListWidget == nullptr )
		return false;
	auto currentFavoriteItem = musicListWidget->getCurrentFavoriteItem( );
	if( currentFavoriteItem == nullptr )
		return false;
	if( currentFavoriteItem->updateItem( music_item ) == false )
		return false;
	return true;
}
bool MusicWindow::removeItem( MusicItem *music_item ) {
	if( musicCentreWidget == nullptr )
		return false;
	auto musicListWidget = musicCentreWidget->getMusicListWidget( );
	if( musicListWidget == nullptr )
		return false;
	auto currentFavoriteItem = musicListWidget->getCurrentFavoriteItem( );
	if( currentFavoriteItem == nullptr )
		return false;
	if( currentFavoriteItem->removeItem( music_item ) == false )
		return false;
	return true;
}

MusicCentreWidget * MusicWindow::getMusicCentreWidget( ) const {
	return musicCentreWidget;
}

void MusicWindow::clear( ) {
	MusicListWidget *musicListWidget;
	if( musicCentreWidget ) {
		musicListWidget = musicCentreWidget->getMusicListWidget( );
		if( musicListWidget ) {
			userMutex->lock( );
			musicListWidget->clear( );
			userMutex->unlock( );
		}
	}
}
