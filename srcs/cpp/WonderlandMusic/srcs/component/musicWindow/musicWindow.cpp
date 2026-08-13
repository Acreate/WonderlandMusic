#include "musicWindow.h"

#include <QJsonObject>

#include "../../application/jsonKey/appMusicManageJsonKey.h"
#include "../../application/translate/musicWindowTranslate.h"

#include "../../head/after_init_macro.h"
#include "../../head/before_init_macro.h"
#include "../../head/init_macro.h"
#include "../../head/release_macro.h"

#include "../../mutex/userMutex.h"
#include "../../tools/pathTools.h"

#include "musicCentreWidget/musicCentreWidget.h"

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
		return true;
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

MusicCentreWidget * MusicWindow::getMusicCentreWidget( ) const {
	return musicCentreWidget;
}
bool MusicWindow::setMusicFavoriteMenu( IMusicFavoriteMenu *music_favorite_menu ) {
	if( musicCentreWidget == nullptr )
		return false;
	return musicCentreWidget->setMusicFavoriteMenu( music_favorite_menu );
}
bool MusicWindow::setMusicListMenu( IMusicListMenu *music_list_menu ) {
	if( musicCentreWidget == nullptr )
		return false;
	return musicCentreWidget->setMusicListMenu( music_list_menu );
}
bool MusicWindow::readJsonData( ) {
	return true;
}
bool MusicWindow::writeJsonData( ) {
	if( AppJsonKeyTools::getAppMusicManage( [this] ( const AppMusicManageJsonKey &json_key ) {
		QJsonObject jsonObject;
		if( musicCentreWidget->getJsonData( jsonObject ) == false )
			return false;
		QJsonObject musicWindowJson;
		musicWindowJson.insert( "musicCentreWidget", jsonObject );
		if( PathTools::writeJsonObject( musicWindowJson, json_key.getFilePath( ) ) == false )
			return false;
		return true;
	} ) == false )
		return false;
	return true;
}
