#include "musicWindow.h"

#include "../../application/translate/musicWindowTranslate.h"

#include "../../head/after_init_macro.h"
#include "../../head/before_init_macro.h"
#include "../../head/init_macro.h"
#include "../../head/release_macro.h"

#include "../../tools/appTranslateTools.h"

#include "musicCentreWidget/musicCentreWidget.h"
MusicWindow::MusicWindow( ) {
}
bool MusicWindow::deleteResource( ) {
	Delete_Resource_App_Core_Ptr( musicCentreWidget );
	return true;
}
bool MusicWindow::initBefore( ) {
	deleteResource( );
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
