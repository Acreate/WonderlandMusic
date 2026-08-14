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
	if( AppJsonKeyTools::getAppMusicManage( [this, &get_json_object] ( const AppMusicManageJsonKey &json_key ) {
		QJsonObject jsonObject;
		if( musicCentreWidget->getJsonData( jsonObject ) == false )
			return false;
		get_json_object.insert( json_key.getMusicCentreWidgetKey( ), jsonObject );
		return true;
	} ) == false )
		return false;

	return true;
}
bool MusicWindow::setJsonData( const QJsonObject &set_json_object ) {
	if( AppJsonKeyTools::getAppMusicManage( [this, &set_json_object] ( const AppMusicManageJsonKey &json_key ) {
		// 获取量
		size_t getIndex = 0;
		// 原始量
		size_t count = 1;
		auto end = set_json_object.end( );
		auto iterator = set_json_object.begin( );
		auto &musicCentreWidgetKey = json_key.getMusicCentreWidgetKey( );
		for( ; iterator != end; ++iterator ) {
			auto key = iterator.key( );
			if( key == musicCentreWidgetKey ) {
				getIndex += 1;
				auto jsonObejct = iterator.value( ).toObject( );
				if( musicCentreWidget->setJsonData( jsonObejct ) == false )
					return false;
			}
		}

		if( getIndex != count )
			return false;
		return true;
	} ) == false )
		return false;

	return true;
}
const char * MusicWindow::getTypeName( ) const {
	return metaObject( )->className( );
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
bool MusicWindow::showPanelBefore( ) {
	return true;
}
bool MusicWindow::hidePanelBefore( ) {
	return true;
}
bool MusicWindow::releasePanelBefore( ) {
	return true;
}
