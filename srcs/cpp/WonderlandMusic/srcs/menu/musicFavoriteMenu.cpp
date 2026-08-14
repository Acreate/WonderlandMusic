#include "musicFavoriteMenu.h"

#include <QJsonObject>

#include "../application/appMenuManage.h"
#include "../application/jsonKey/musicFavoriteMenuJsonKey.h"
#include "../application/translate/musicFavoriteMenuTranslate.h"

#include "../component/musicWindow/musicWindow.h"
#include "../component/musicWindow/Item/favoriteItem/favoriteItem.h"
#include "../component/musicWindow/musicCentreWidget/musicCentreWidget.h"
#include "../component/musicWindow/musicCentreWidget/musicFavoriteWidget/musicFavoriteWidget.h"

#include "../head/release_macro.h"

#include "../tools/appJsonKeyTools.h"
#include "../tools/instanceTools.h"
#include "../tools/pathInfoTools.h"
#include "../tools/widgetTools.h"
MusicFavoriteMenu::MusicFavoriteMenu( ) {
}
MusicFavoriteMenu::~MusicFavoriteMenu( ) {
	deleteResource( );
}
bool MusicFavoriteMenu::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( createFavoriteItemAction );
	Delete_Resource_App_Core_Ptr( renameFavoriteItemAction );
	Delete_Resource_App_Core_Ptr( deleteFavoriteItemAction );
	Delete_Resource_App_Core_Ptr( addMusicFileAction );
	Delete_Resource_App_Core_Ptr( addMusicDirAction );
	return true;
}
bool MusicFavoriteMenu::initBefore( ) {
	deleteResource( );
	createFavoriteItemAction = addAction( "" );
	renameFavoriteItemAction = addAction( "" );
	deleteFavoriteItemAction = addAction( "" );
	addMusicFileAction = addAction( "" );
	addMusicDirAction = addAction( "" );
	return true;
}
bool MusicFavoriteMenu::init( ) {
	return true;
}
bool MusicFavoriteMenu::initAfter( ) {
	if( AppTranslateTools::getMusicFavoriteMenu( [this] ( MusicFavoriteMenuTranslate &translate ) {
		createFavoriteItemAction->setText( translate.getCreateFavoriteItem( ) );
		return true;
	} ) == false )
		return false;
	auto signal = &QAction::triggered;
	connect( createFavoriteItemAction, signal, this, &MusicFavoriteMenu::slot_createFavoriteItem );
	connect( renameFavoriteItemAction, signal, this, &MusicFavoriteMenu::slot_renameFavoriteItem );
	connect( deleteFavoriteItemAction, signal, this, &MusicFavoriteMenu::slot_deleteFavoriteItem );
	connect( addMusicFileAction, signal, this, &MusicFavoriteMenu::slot_addMusicFile );
	connect( addMusicDirAction, signal, this, &MusicFavoriteMenu::slot_addMusicDir );
	return true;
}
bool MusicFavoriteMenu::getJsonData( QJsonObject &get_json_object ) const {
	if( AppJsonKeyTools::getMusicFavoriteMenu( [&get_json_object, this] ( const MusicFavoriteMenuJsonKey &json_key ) {
		get_json_object.insert( json_key.getLoadMultDir( ), openSelecteMultiDirWidgetPath );
		get_json_object.insert( json_key.getLoadMultFile( ), openSelecteMultiFileWidgetPath );
		return true;
	} ) == false )
		return false;
	return true;
}
bool MusicFavoriteMenu::setJsonData( const QJsonObject &set_json_object ) {
	if( AppJsonKeyTools::getMusicFavoriteMenu( [&set_json_object, this] ( const MusicFavoriteMenuJsonKey &json_key ) {
		auto end = set_json_object.end( );
		auto iterator = set_json_object.find( json_key.getLoadMultDir( ) );
		if( iterator == end )
			return false;
		openSelecteMultiDirWidgetPath = iterator.value( ).toString( );
		iterator = set_json_object.find( json_key.getLoadMultFile( ) );
		if( iterator == end )
			return false;
		openSelecteMultiFileWidgetPath = iterator.value( ).toString( );
		return true;
	} ) == false )
		return false;
	return true;
}
bool MusicFavoriteMenu::execMenu( MusicFavoriteWidget *music_favorite_widget, FavoriteItem *favorite_item, const QPoint &mouse_global_point ) {
	if( music_favorite_widget == nullptr )
		return false;
	musicFavoriteWidget = music_favorite_widget;
	favoriteItem = favorite_item;

	if( AppTranslateTools::getMusicFavoriteMenu( [this] ( MusicFavoriteMenuTranslate &translate ) {
		if( favoriteItem ) {
			auto &favoriteItemName = favoriteItem->getFavoriteItemName( );
			renameFavoriteItemAction->setText( translate.getRenameFavoriteItem( ).arg( favoriteItemName ) );
			renameFavoriteItemAction->setEnabled( true );
			deleteFavoriteItemAction->setText( translate.getDeleteFavoriteItem( ).arg( favoriteItemName ) );
			deleteFavoriteItemAction->setEnabled( true );
			addMusicFileAction->setText( translate.getAddMusicFileToFavoriteItem( ).arg( favoriteItemName ) );
			addMusicFileAction->setEnabled( true );
			addMusicDirAction->setText( translate.getAddMusicDirToFavoriteItem( ).arg( favoriteItemName ) );
			addMusicDirAction->setEnabled( true );
		} else {
			renameFavoriteItemAction->setText( translate.getIllegalRenameFavoriteItem( ) );
			renameFavoriteItemAction->setEnabled( false );
			deleteFavoriteItemAction->setText( translate.getIllegalDeleteFavoriteItem( ) );
			deleteFavoriteItemAction->setEnabled( false );
			addMusicFileAction->setText( translate.getIllegalAddMusicFileToFavoriteItem( ) );
			addMusicFileAction->setEnabled( false );
			addMusicDirAction->setText( translate.getIllegalAddMusicDirToFavoriteItem( ) );
			addMusicDirAction->setEnabled( false );
		}
		return true;
	} ) == false )
		return false;

	return InstanceTools::getAppMenuManage( )->popMusicFavoriteMenu( mouse_global_point );
}
void MusicFavoriteMenu::hideEvent( QHideEvent *hide_event ) {
	QMenu::hideEvent( hide_event );
}
void MusicFavoriteMenu::slot_createFavoriteItem( ) {
	if( musicFavoriteWidget == nullptr )
		return;
	musicFavoriteWidget->opendCreateFavoriteItemWidget( );
}
void MusicFavoriteMenu::slot_renameFavoriteItem( ) {
	if( musicFavoriteWidget == nullptr || favoriteItem == nullptr )
		return;
	musicFavoriteWidget->opendRenameFavoriteItemWidget( favoriteItem );
}
void MusicFavoriteMenu::slot_deleteFavoriteItem( ) {
	if( musicFavoriteWidget == nullptr || favoriteItem == nullptr )
		return;
	if( musicFavoriteWidget->removeItem( favoriteItem ) == false )
		return;
	delete favoriteItem;
	musicFavoriteWidget->repaint( );
}
void MusicFavoriteMenu::slot_addMusicFile( ) {
	AppTranslateTools::getMusicFavoriteMenu( [this] ( MusicFavoriteMenuTranslate &translate ) {
		if( favoriteItem == nullptr )
			return false;
		std::vector< QString > resultFile;
		auto musicCentreWidget = musicFavoriteWidget->getMusicCentreWidget( );
		QWidget *openWidget = musicCentreWidget->getMusicWindow( );
		QString filter;
		if( PathInfoTools::getSupperDecodeFileSuffixFilter( filter ) == false )
			return false;
		if( WidgetTools::showMultipleSelectFileDialog( resultFile, openSelecteMultiFileWidgetPath, openWidget, translate.getSelectMusicFile( ), filter ) == false )
			return false;
		favoriteItem->loadMusicFile( resultFile );
		favoriteItem->update( );
		return true;
	} );
}
void MusicFavoriteMenu::slot_addMusicDir( ) {
	AppTranslateTools::getMusicFavoriteMenu( [this] ( MusicFavoriteMenuTranslate &translate ) {
		if( favoriteItem == nullptr )
			return false;
		std::vector< QString > resultFile;
		auto musicCentreWidget = musicFavoriteWidget->getMusicCentreWidget( );
		QWidget *openWidget = musicCentreWidget->getMusicWindow( );
		if( WidgetTools::showMultipleSelectDirDialog( resultFile, openSelecteMultiDirWidgetPath, openWidget, translate.getSelectMusicFile( ) ) == false )
			return false;
		favoriteItem->loadMusicFile( resultFile );
		favoriteItem->update( );
		return true;
	} );
}
QMenu * MusicFavoriteMenu::toMenu( ) {
	return this;
}
