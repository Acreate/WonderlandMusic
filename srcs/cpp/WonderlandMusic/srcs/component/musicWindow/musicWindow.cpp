#include "musicWindow.h"

#include "../../application/appInstance.h"
#include "../../application/appMusicDecoder.h"
#include "../../application/translate/musicWindowTranslate.h"

#include "../../head/after_init_macro.h"
#include "../../head/before_init_macro.h"
#include "../../head/init_macro.h"
#include "../../head/release_macro.h"

#include "../../mutex/userMutex.h"

#include "../../tools/appTranslateTools.h"
#include "../../tools/pathTools.h"

#include "favoriteDockWidget/favoriteDockWidget.h"

#include "musicCentreWidget/musicCentreWidget.h"

#include "musicItem/musicItem.h"

#include "musicTitleDockWidget/musicTitleDockWidget.h"

#include "musicToolDockWidget/musicToolDockWidget.h"
MusicWindow::MusicWindow( ) {
}
bool MusicWindow::deleteResource( ) {
	if( userMutex == nullptr )
		return true;
	userMutex->lock( );
	unSafetyClearInfo( );
	Delete_Resource_App_Core_Ptr( musicCentreWidget );
	Delete_Resource_App_Core_Ptr( favoriteDockWidget );
	Delete_Resource_App_Core_Ptr( musicTitleDockWidget );
	Delete_Resource_App_Core_Ptr( musicToolDockWidget );
	userMutex->unlock( );
	Delete_Resource_App_Core_Ptr( userMutex );
	return true;
}
void MusicWindow::unSafetyClearInfo( ) {
	size_t count = musicItemVector.size( );
	if( count ) {
		auto musicItem = musicItemVector.data( );
		size_t index;
		for( index = 0; index < count; index += 1 ) {
			musicItem[ index ]->musicWindow = nullptr;
			delete musicItem;
		}
		musicItemVector.clear( );
		unSafetyClearShow( );
	}
}
void MusicWindow::unSafetyClearShow( ) {
	if( musicCentreWidget )
		musicCentreWidget->clearShowMusic( );
}
bool MusicWindow::initBefore( ) {
	deleteResource( );
	userMutex = new UserMutex;
	musicCentreWidget = new MusicCentreWidget( this );
	favoriteDockWidget = new FavoriteDockWidget( this );
	musicTitleDockWidget = new MusicTitleDockWidget( this );
	musicToolDockWidget = new MusicToolDockWidget( this );
	Before_Init_Resource_App_Core_Ptr( musicCentreWidget );
	Before_Init_Resource_App_Core_Ptr( favoriteDockWidget );
	Before_Init_Resource_App_Core_Ptr( musicTitleDockWidget );
	Before_Init_Resource_App_Core_Ptr( musicToolDockWidget );
	return true;
}
bool MusicWindow::init( ) {
	if( AppTranslateTools::getMusicWindow( [this] ( MusicWindowTranslate &translate ) {
		setName( translate.getTitleName( ) );
	} ) == false )
		setName( tr( "音乐" ) );
	Init_Resource_App_Core_Ptr( musicCentreWidget );
	Init_Resource_App_Core_Ptr( favoriteDockWidget );
	Init_Resource_App_Core_Ptr( musicTitleDockWidget );
	Init_Resource_App_Core_Ptr( musicToolDockWidget );
	return true;
}
bool MusicWindow::initAfter( ) {
	After_Init_Resource_App_Core_Ptr( musicCentreWidget );
	After_Init_Resource_App_Core_Ptr( favoriteDockWidget );
	After_Init_Resource_App_Core_Ptr( musicTitleDockWidget );
	After_Init_Resource_App_Core_Ptr( musicToolDockWidget );
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
	userMutex->lock( );

	size_t count = musicItemVector.size( );
	bool cond = false;
	if( count ) {
		auto musicItem = musicItemVector.data( );
		for( result_index = 0; result_index < count; result_index += 1 )
			if( cond = musicItem[ result_index ] == music_item, cond )
				break;
	}
	userMutex->unlock( );
	return cond;
}
bool MusicWindow::addItem( MusicItem *music_item ) {
	size_t index;
	if( hasItem( index, music_item ) == true )
		return updateItem( music_item );
	music_item->musicWindow = this;
	updateWindow( );
	return false;
}
bool MusicWindow::updateItem( MusicItem *music_item ) {
	if( music_item->musicWindow != this )
		return false;
	updateWindow( );
	return true;
}
bool MusicWindow::removeItem( MusicItem *music_item ) {
	if( music_item->musicWindow != this )
		return false;
	size_t index;
	if( hasItem( index, music_item ) == false )
		return false;
	userMutex->lock( );
	musicItemVector.erase( musicItemVector.begin( ) + index );
	userMutex->unlock( );
	updateWindow( );
	return true;
}
void MusicWindow::updateWindow( ) {
}
void MusicWindow::updateWindow( const QRect &update_rect ) {
}
void MusicWindow::clear( ) {
	userMutex->lock( );
	unSafetyClearInfo( );
	userMutex->unlock( );
}
