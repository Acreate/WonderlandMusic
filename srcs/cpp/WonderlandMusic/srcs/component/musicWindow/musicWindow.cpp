#include "musicWindow.h"

#include <QJsonObject>

#include "../../application/appInstance.h"
#include "../../application/translate/musicWindowTranslate.h"

#include "../../head/after_init_macro.h"
#include "../../head/before_init_macro.h"
#include "../../head/init_macro.h"
#include "../../head/release_macro.h"

#include "../../mutex/userMutex.h"
#include "../../tools/pathTools.h"

#include "musicCentreWidget/musicCentreWidget.h"
#include "musicCentreWidget/musicListWidget/musicListWidget.h"

#include "musicItem/musicItem.h"

MusicWindow::MusicWindow( ) {
}
MusicWindow::~MusicWindow( ) {
	deleteResource( );
}
bool MusicWindow::deleteResource( ) {
	if( userMutex == nullptr )
		return true;
	userMutex->lock( );

	unSafetyClearInfo( );
	Delete_Resource_App_Core_Ptr( musicCentreWidget );
	userMutex->unlock( );
	Delete_Resource_App_Core_Ptr( userMutex );
	return true;
}
bool MusicWindow::unSafetyClearInfo( ) {
	if( musicCentreWidget == nullptr )
		return false;
	auto musicListWidget = musicCentreWidget->getMusicListWidget( );
	if( musicListWidget == nullptr )
		return false;
	return musicListWidget->unSafetyClearInfo( );
}
bool MusicWindow::unSafetyClearShow( ) {
	if( musicCentreWidget )
		return false;
	auto musicListWidget = musicCentreWidget->getMusicListWidget( );
	if( musicListWidget == nullptr )
		return false;
	return musicListWidget->unSafetyClearShow( );
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
	if( music_item->musicWindow != this )
		return false;
	if( musicCentreWidget == nullptr )
		return false;
	auto musicListWidget = musicCentreWidget->getMusicListWidget( );
	if( musicListWidget == nullptr )
		return false;
	return musicListWidget->hasItem( result_index, music_item );
}
bool MusicWindow::addItem( MusicItem *music_item ) {
	if( musicCentreWidget == nullptr )
		return false;
	auto musicListWidget = musicCentreWidget->getMusicListWidget( );
	if( musicListWidget == nullptr )
		return false;
	return musicListWidget->addItem( music_item );
}
bool MusicWindow::updateItem( MusicItem *music_item ) {
	if( musicCentreWidget == nullptr )
		return false;
	auto musicListWidget = musicCentreWidget->getMusicListWidget( );
	if( musicListWidget == nullptr )
		return false;
	if( musicListWidget->updateItem( music_item ) == false )
		return false;
	return true;
}
bool MusicWindow::removeItem( MusicItem *music_item ) {
	if( musicCentreWidget == nullptr )
		return false;
	auto musicListWidget = musicCentreWidget->getMusicListWidget( );
	if( musicListWidget == nullptr )
		return false;
	if( musicListWidget->removeItem( music_item ) == false )
		return false;
	return true;
}
MusicItem * MusicWindow::fromJsonGenerateMusicItem( const QJsonObject &json_object ) {
	if( json_object.empty( ) )
		return nullptr;
	MusicItem *musicItem = new MusicItem( this );
	if( musicItem->setJsonData( json_object ) == false ) {
		delete musicItem;
		return nullptr;
	}
	return musicItem;
}

void MusicWindow::clear( ) {
	userMutex->lock( );
	unSafetyClearInfo( );
	userMutex->unlock( );
}
