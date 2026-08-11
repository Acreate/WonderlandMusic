#include "musicFavoriteMenu.h"

#include "../application/appMenuManage.h"
#include "../application/translate/musicFavoriteMenuTranslate.h"

#include "../component/musicWindow/Item/favoriteItem/favoriteItem.h"

#include "../head/release_macro.h"

#include "../tools/appTranslateTools.h"
#include "../tools/instanceTools.h"
MusicFavoriteMenu::MusicFavoriteMenu( ) {
}
MusicFavoriteMenu::~MusicFavoriteMenu( ) {
	deleteResource( );
}
bool MusicFavoriteMenu::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( deleteFavoriteItemAction );
	Delete_Resource_App_Core_Ptr( addMusicFile );
	Delete_Resource_App_Core_Ptr( addMusicDir );
	return true;
}
bool MusicFavoriteMenu::initBefore( ) {
	deleteResource( );
	createFavoriteItemAction = addAction( "" );
	renameFavoriteItemAction = addAction( "" );
	deleteFavoriteItemAction = addAction( "" );
	addMusicFile = addAction( "" );
	addMusicDir = addAction( "" );
	return true;
}
bool MusicFavoriteMenu::init( ) {
	return true;
}
bool MusicFavoriteMenu::initAfter( ) {
	if( AppTranslateTools::getMusicFavoriteMenu( [this] ( MusicFavoriteMenuTranslate &translate ) {
		createFavoriteItemAction->setText( translate.getCreateFavoriteItem( ) );
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
			addMusicFile->setText( translate.getAddMusicFileToFavoriteItem( ).arg( favoriteItemName ) );
			addMusicFile->setEnabled( true );
			addMusicDir->setText( translate.getAddMusicDirToFavoriteItem( ).arg( favoriteItemName ) );
			addMusicDir->setEnabled( true );
		} else {
			renameFavoriteItemAction->setText( translate.getIllegalRenameFavoriteItem( ) );
			renameFavoriteItemAction->setEnabled( false );
			deleteFavoriteItemAction->setText( translate.getIllegalDeleteFavoriteItem( ) );
			deleteFavoriteItemAction->setEnabled( false );
			addMusicFile->setText( translate.getIllegalAddMusicFileToFavoriteItem( ) );
			addMusicFile->setEnabled( false );
			addMusicDir->setText( translate.getIllegalAddMusicDirToFavoriteItem( ) );
			addMusicDir->setEnabled( false );
		}
	} ) == false )
		return false;

	return InstanceTools::getAppMenuManage( )->popMusicFavoriteMenu( mouse_global_point );
}
void MusicFavoriteMenu::hideEvent( QHideEvent *hide_event ) {
	QMenu::hideEvent( hide_event );
	oldFavoriteItem = favoriteItem;
	musicFavoriteWidget = nullptr;
	favoriteItem = nullptr;
}
QMenu * MusicFavoriteMenu::toMenu( ) {
	return this;
}
