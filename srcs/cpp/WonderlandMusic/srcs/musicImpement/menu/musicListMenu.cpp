#include "musicListMenu.h"

#include <application/appInstance/appUserInterfaceManage/appMenuManage.h>

#include <tools/instanceTools.h>

#include "../../application/appInstance/appDataManage/translate/messageTranslate.h"
#include "../../application/appInstance/appDataManage/translate/musicListMenuTranslate.h"

#include "../../mutex/userMutex.h"
MusicListMenu::MusicListMenu( ) {
	appendTypeInfo( this );
}
MusicListMenu::~MusicListMenu( ) {
	deleteResource( );
}
bool MusicListMenu::deleteResource( ) {
	if( userMutex == nullptr )
		return true;
	clear( );
	playMusicItem = nullptr;
	removeMusicItem = nullptr;
	deleteMusicItem = nullptr;
	moveToTopMusicItem = nullptr;
	moveToBottomMusicItem = nullptr;
	moveToPlayTopMusicItem = nullptr;
	moveToPlayBottomMusicItem = nullptr;
	return true;
}
bool MusicListMenu::initBefore( ) {
	deleteResource( );
	userMutex = new UserMutex;
	playMusicItem = addAction( "" );
	addSeparator( );
	removeMusicItem = addAction( "" );
	deleteMusicItem = addAction( "" );
	addSeparator( );
	moveToTopMusicItem = addAction( "" );
	moveToBottomMusicItem = addAction( "" );
	addSeparator( );
	moveToPlayTopMusicItem = addAction( "" );
	moveToPlayBottomMusicItem = addAction( "" );
	return true;
}
bool MusicListMenu::init( ) {
	return true;
}
bool MusicListMenu::initAfter( ) {
	if( AppTranslateTools::getMusicListMenu( [this] ( MusicListMenuTranslate &translate ) {
		playMusicItem->setText( translate.getPlayMusicItem( ) );
		removeMusicItem->setText( translate.getRemoveMusicItem( ) );
		deleteMusicItem->setText( translate.getDeleteMusicItem( ) );
		moveToTopMusicItem->setText( translate.getMoveToTopMusicItem( ) );
		moveToBottomMusicItem->setText( translate.getMoveToBottomMusicItem( ) );
		moveToPlayTopMusicItem->setText( translate.getMoveToPlayTopMusicItem( ) );
		moveToPlayBottomMusicItem->setText( translate.getMoveToPlayBottomMusicItem( ) );
		return true;
	} ) == false )
		return false;
	return true;
}
bool MusicListMenu::getJsonData( QJsonObject &get_json_object ) const {
	return true;
}
bool MusicListMenu::setJsonData( const QJsonObject &set_json_object ) {
	return true;
}
IMusicCentreWidget * MusicListMenu::getMusicCentreWidget( ) const {
	return musicCentreWidget;
}
bool MusicListMenu::setMusicCentreWidget( IMusicCentreWidget *music_centre_widget ) {
	musicCentreWidget = music_centre_widget;
	return true;
}
bool MusicListMenu::execMenu( IMusicListWidget *music_list_widget, IMusicItem *music_item, const QPoint &mouse_global_point ) {
	return InstanceTools::getAppMenuManage( )->popMusicListMenu( mouse_global_point );
}

QMenu * MusicListMenu::toMenu( ) {
	return this;
}
