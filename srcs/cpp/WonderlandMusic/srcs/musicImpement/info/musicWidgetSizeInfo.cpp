#include "musicWidgetSizeInfo.h"

#include <qfontmetrics.h>

#include <application/appInstance/applicationManage.h>
#include <application/appInstance/appUserInterfaceManage/appDrawManage/appRenderImage.h>

#include <tools/instanceTools.h>

#include "../../application/appInstance/appDataManage/jsonKey/musicWidgetSizeInfoJsonKey.h"
MusicWidgetSizeInfo::MusicWidgetSizeInfo( ) {
	appendTypeInfo( this );
}
MusicWidgetSizeInfo::~MusicWidgetSizeInfo( ) {
}
bool MusicWidgetSizeInfo::setMusicCentreWidget( IMusicCentreWidget *music_centre_widget ) {
	musicCentreWidget = music_centre_widget;
	return true;
}
bool MusicWidgetSizeInfo::initInfo( ) {
	auto appRenderImage = InstanceTools::getAppRenderImage( );
	if( appRenderImage == nullptr )
		return false;

	auto fontMetrics = appRenderImage->getFontMetrics( );
	if( fontMetrics == nullptr )
		return false;
	auto applicationManage = InstanceTools::getApplicationManage( );
	if( applicationManage == nullptr )
		return false;
	auto metrics = applicationManage->fontMetrics( );
	QString defaultWidth = QObject::tr( "默认" );
	favoriteWidth = metrics.horizontalAdvance( defaultWidth );
	titleHeight = metrics.height( );
	return true;
}

int MusicWidgetSizeInfo::getFavoriteWidth( ) const {
	return favoriteWidth;
}
int MusicWidgetSizeInfo::getTitleHeight( ) const {
	return titleHeight;
}
bool MusicWidgetSizeInfo::updateMusicWidgetLayout( ) {
	return false;
}
bool MusicWidgetSizeInfo::getJsonData( QJsonObject &get_json_object ) const {
	if( AppJsonKeyTools::getMusicWidgetSizeInfo( [] ( const MusicWidgetSizeInfoJsonKey &json_key ) {
		return true;
	} ) == false )
		return false;
	return true;
}
bool MusicWidgetSizeInfo::setJsonData( const QJsonObject &set_json_object ) {
	if( AppJsonKeyTools::getMusicWidgetSizeInfo( [] ( const MusicWidgetSizeInfoJsonKey &json_key ) {
		return true;
	} ) == false )
		return false;
	return true;
}
IMusicCentreWidget * MusicWidgetSizeInfo::getMusicCentreWidget( ) const {
	return musicCentreWidget;
}
int MusicWidgetSizeInfo::setFavoriteWidth( const int &favoriet_width ) {
	int old = favoriet_width;
	favoriteWidth = old;
	return old;
}
int MusicWidgetSizeInfo::setTitleHeight( const int &title_height ) {
	int old = titleHeight;
	titleHeight = title_height;
	return old;
}
