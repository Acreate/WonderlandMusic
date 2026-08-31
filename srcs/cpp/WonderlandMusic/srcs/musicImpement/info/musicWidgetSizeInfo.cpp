#include "musicWidgetSizeInfo.h"

#include <qfontmetrics.h>

#include <application/appInstance/applicationManage.h>
#include <application/appInstance/appUserInterfaceManage/appDrawManage/appRenderImage.h>

#include <tools/instanceTools.h>

#include "../../application/appInstance/appDataManage/jsonKey/appDataManageJsonKey.h"
#include "../../application/appInstance/appDataManage/jsonKey/musicWidgetSizeInfoJsonKey.h"
MusicWidgetSizeInfo::MusicWidgetSizeInfo( ) {
	appendTypeInfo( this );
}
MusicWidgetSizeInfo::~MusicWidgetSizeInfo( ) {
}
bool MusicWidgetSizeInfo::setMusicCentreWidget( MusicCentreWidget *music_centre_widget ) {
	musicCentreWidget = music_centre_widget;
	return false;
}
int MusicWidgetSizeInfo::getFavoriteWidth( ) const {
	QString defaultWidth = QObject::tr( "默认" );
	auto appRenderImage = InstanceTools::getAppRenderImage( );
	if( appRenderImage ) {
		auto fontMetrics = appRenderImage->getFontMetrics( );
		if( fontMetrics )
			return fontMetrics->horizontalAdvance( defaultWidth );
	}
	auto applicationManage = InstanceTools::getApplicationManage( );
	if( applicationManage == nullptr )
		return 50;
	auto metrics = applicationManage->fontMetrics( );
	return metrics.horizontalAdvance( defaultWidth );
}
int MusicWidgetSizeInfo::getTitleHeight( ) const {
	QString defaultWidth = QObject::tr( "默认" );
	auto appRenderImage = InstanceTools::getAppRenderImage( );
	if( appRenderImage ) {
		auto fontMetrics = appRenderImage->getFontMetrics( );
		if( fontMetrics )
			return fontMetrics->height( );
	}
	auto applicationManage = InstanceTools::getApplicationManage( );
	if( applicationManage == nullptr )
		return 50;
	auto metrics = applicationManage->fontMetrics( );
	return metrics.height( );
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
MusicCentreWidget * MusicWidgetSizeInfo::getMusicCentreWidget( ) const {
	return musicCentreWidget;
}
int MusicWidgetSizeInfo::setFavoriteWidth( const int &favoriet_width ) {
	return 0;
}
int MusicWidgetSizeInfo::setTitleHeight( const int &favoriet_width ) {
	return 0;
}
