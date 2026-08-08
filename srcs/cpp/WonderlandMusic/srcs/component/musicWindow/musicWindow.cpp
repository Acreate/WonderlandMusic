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

MusicCentreWidget * MusicWindow::getMusicCentreWidget( ) const {
	return musicCentreWidget;
}
